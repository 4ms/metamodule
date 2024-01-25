#include "updater_proxy.hh"
#include "pr_dbg.hh"
#include "ram_buffer.hh"
#include "manifest_parse.hh"
#include <cassert>

namespace MetaModule
{

auto GetTargetForUpdateType = [](UpdateType val) -> std::optional<IntercoreStorageMessage::FlashTarget>
{
	switch (val)
	{
		case UpdateType::Wifi: return IntercoreStorageMessage::FlashTarget::WIFI;
		case UpdateType::App: return IntercoreStorageMessage::FlashTarget::QSPI;
		default: return std::nullopt;
	}
};

FirmwareUpdaterProxy::FirmwareUpdaterProxy(FileStorageProxy &file_storage)
    : file_storage{file_storage}
	, state(Idle)
	, sharedMem(nullptr)
{
	auto ram_buffer = get_ram_buffer_client();
	assert(ram_buffer.size() >= sizeof(SharedMem));

	sharedMem = new (ram_buffer.data()) SharedMem;
}

bool FirmwareUpdaterProxy::start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize)
{
    if (manifest_filesize <= sizeof(SharedMem::manifestBuffer))
    {
		manifestBuffer = std::span<char>((char*)sharedMem->manifestBuffer.data(), manifest_filesize);

		pr_dbg("%p + %u\n", manifestBuffer.data(), manifestBuffer.size());

	    if (file_storage.request_load_file(manifest_filename, manifest_file_vol, manifestBuffer))
        {
            vol = manifest_file_vol;
            moveToState(State::LoadingManifest);
            return true;
        }
        else
        {
            abortWithMessage("Cannot request manifest file");
        }
    }
    else
    {
        abortWithMessage("Manifest file is too large");
    }

    return false;		
}

FirmwareUpdaterProxy::Status FirmwareUpdaterProxy::process()
{
    switch (state) {
        case Idle:
        case Success:
        case Error:
            break;

        case LoadingManifest:
		{
		    auto message = file_storage.get_message();

            if (message.message_type == FileStorageProxy::LoadFileToRamSuccess)
            {
                ManifestParser parser;

                auto parseResult = parser.parse(manifestBuffer);

                if (parseResult and parseResult->files.size() > 0) {
                    manifest = *parseResult;

                    current_file_idx = 0;                    
                    moveToState(State::Verifying);

                } else {
                    abortWithMessage("Manifest file is invalid");
                }

            } else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
                abortWithMessage("Failed reading manifest file");
            }

        } break;

		case Verifying:
		{
			if (justEnteredState)
			{
				justEnteredState = false;
				pr_dbg("Start verifying file %u of %u\n", current_file_idx, manifest.files.size());

				auto& thisFile = manifest.files[current_file_idx];

				if (auto target = GetTargetForUpdateType(thisFile.type); target)
				{
					if (auto checksumValue = thisFile.md5; checksumValue)
					{
						sharedMem->bytes_processed = 0;
						current_file_size = thisFile.filesize;
						current_file_name = thisFile.name;

						auto result = file_storage.request_checksum_compare(*target, *checksumValue, thisFile.address, thisFile.filesize, &sharedMem->bytes_processed);

						if (not result)
						{
							abortWithMessage("Cannot trigger comparing checksums");
						}	
					}
					else
					{
						pr_dbg("Skipping verify step because no checksum is defined");
						moveToState(Writing);
					}				
				}
				else
				{
					abortWithMessage("Invalid update file type");
				}
			}
			else
			{
				switch (file_storage.get_message().message_type)
				{
					case FileStorageProxy::ChecksumMatch:
						proceedWithNextFile();
						break;

					case FileStorageProxy::ChecksumMismatch:
						moveToState(Writing);
						break;

					case FileStorageProxy::ChecksumFailed:
						abortWithMessage("Error when comparing checksums");
						break;

					default:
						break;
				}
			}
		} break;

		case Writing:
		{
			if (justEnteredState)
			{
				justEnteredState = false;
				pr_dbg("Start flashing file %u of %u\n", current_file_idx, manifest.files.size());

				auto& thisFile = manifest.files[current_file_idx];

				sharedMem->bytes_processed = 0;
				current_file_size = thisFile.filesize;
				current_file_name = thisFile.name;

				if (auto target = GetTargetForUpdateType(thisFile.type); target)
				{
					auto result = file_storage.request_file_flash(*target, thisFile.filename, vol, thisFile.address, thisFile.filesize, &sharedMem->bytes_processed);

					if (not result)
					{
						abortWithMessage("Cannot trigger flashing");
					}
				}
				else
				{
					abortWithMessage("Invalid update file type");
				}
			}
			else
			{
				switch (file_storage.get_message().message_type)
				{
					case FileStorageProxy::FlashingOk:
						proceedWithNextFile();
						break;

					case FileStorageProxy::FlashingFailed:
						abortWithMessage("Error when flashing file");
						break;

					default:
						break;
				}
			}

		} break;

		default:
			pr_err("Undefined state\n");
			abortWithMessage("Internal Error");
	}

	return state == State::Error ?
		Status{state, current_file_name, current_file_size, sharedMem->bytes_processed, error_message} :
		Status{state, current_file_name, current_file_size, sharedMem->bytes_processed};    
}

void FirmwareUpdaterProxy::abortWithMessage(const char* message)
{
    state = State::Error;
    error_message = message;
}

void FirmwareUpdaterProxy::proceedWithNextFile()
{
	current_file_idx++;
	if (current_file_idx < manifest.files.size())
	{
		moveToState(Verifying);
	}
	else
	{
		moveToState(Success);
	}
}

void FirmwareUpdaterProxy::moveToState(State newState)
{
	justEnteredState = true;
    pr_trace("Updater: Move state %u -> %u\n", state, newState);
    state = newState;
}


} // namespace MetaModule
