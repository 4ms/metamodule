#include "updater_proxy.hh"
#include "pr_dbg.hh"
#include "ram_buffer.hh"
#include "manifest_parse.hh"

namespace MetaModule
{

FirmwareUpdaterProxy::FirmwareUpdaterProxy(FileStorageProxy &file_storage)
    : file_storage{file_storage}
	, state(Idle)
{
}

bool FirmwareUpdaterProxy::start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize) {

	auto ram_buffer = get_ram_buffer();

    if (manifest_filesize <= 4 * 1024 * 1024)
    {
        manifest_buffer = std::span<char>{(char *)ram_buffer.data(), manifest_filesize};

	    if (file_storage.request_load_file(manifest_filename, manifest_file_vol, manifest_buffer))
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
	std::size_t bytes_completed = 0;

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

                auto parseResult = parser.parse(manifest_buffer);

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
				pr_dbg("Start verify %u\n", current_file_idx);
			}
			else
			{
				// TODO: update progress

				bool success = true;

				if (success)
				{

					bool checksumAlreadyMatches = false;

					if (checksumAlreadyMatches)
					{
						proceedWithNextFile();
					}
					else
					{
						moveToState(Writing);
					}
				}
			}
		} break;

		case Writing:
		{
			if (justEnteredState)
			{
				pr_dbg("Start writing %u\n", current_file_idx);
			}
			else
			{
				// TODO: update progress

				bool success = true;

				if (success)
				{
					proceedWithNextFile();
				}
				else
				{
					abortWithMessage("Failed to write file");
				}
			}

		} break;

		default:
			pr_err("Undefined state\n");
			abortWithMessage("Internal Error");
	}

	justEnteredState = false;

	return state == State::Error ?
		Status{state, current_file_size, bytes_completed, error_message} :
		Status{state, current_file_size, bytes_completed};    
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
    pr_dbg("Update move state %u -> %u\n", state, newState);
    state = newState;
}


} // namespace MetaModule
