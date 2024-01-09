#include "updater.hh"
#include "loaders/flash/firmware_flash_loader.hh"
#include "loaders/wifi/firmware_wifi_loader.hh"
#include "ram_buffer.hh"
#include "manifest_parse.hh"

namespace MetaModule
{

FirmwareUpdater::FirmwareUpdater(FileStorageProxy &file_storage)
    : file_storage{file_storage}
    , state(State::Idle)
    , current_file_idx(0)
    , current_file_size(0)
    , ram_buffer(get_ram_buffer())
{
}

bool FirmwareUpdater::start(std::string_view manifest_filename, Volume manifest_file_vol, uint32_t manifest_filesize) {

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

FirmwareUpdater::Status FirmwareUpdater::process() {
    int bytes_remaining = 0;

    switch (state) {
        case Idle:
        case Success:
        case Error:
            break;

        case LoadingManifest: {
            auto message = file_storage.get_message();

            if (message.message_type == FileStorageProxy::LoadFileToRamSuccess)
            {
                ManifestParser parser;

                auto parseResult = parser.parse(manifest_buffer);

                if (parseResult and parseResult->files.size() > 0) {
                    manifest = *parseResult;

                    current_file_idx = 0;
                    file_images.reserve(manifest.files.size());
                    
                    moveToState(State::StartLoadingFileToRam);

                } else {
                    abortWithMessage("Manifest file is invalid");
                }

            } else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
                abortWithMessage("Failed reading manifest file");
            }

        } break;

        case StartLoadingFileToRam:
        {
            auto success = start_reading_file();
            if (success)
            {
                moveToState(LoadingFileToRAM);
            }
            else
            {
                abortWithMessage("Failed to request loading firmware file to RAM");
            }
        }

        case LoadingFileToRAM: {

            auto message = file_storage.get_message();

            if (message.message_type == FileStorageProxy::LoadFileToRamSuccess)
            {
                pr_trace("A7: file loaded\n");

                if (current_file_idx < manifest.files.size()-1)
                {
                    // Load next file
                    current_file_idx++;
                    moveToState(StartLoadingFileToRam);
                }
                else
                {
                    // Write first file
                    current_file_idx = 0;
                    if (start_writing_file())
                    {
                        moveToState(Writing);
                    }

                }
            }
            else if (message.message_type == FileStorageProxy::LoadFileToRamFailed)
            {
                abortWithMessage("Failed to load a firmware file");
            }

        } break;

        case Writing: {
            auto [bytes_rem, err] = current_file_loader->load_next_block();

            if (err == FileLoaderBase::Error::Failed)
            {
                bytes_remaining = bytes_rem;
                abortWithMessage("Failed writing app to flash");
            }
            else if (bytes_rem > 0)
            {
                bytes_remaining = bytes_rem;
            }
            else
            {
                if (current_file_idx < manifest.files.size()-1)
                {
                    // write next file
                    current_file_idx++;
                    start_writing_file();
                }
                else
                {
                    moveToState(Success);
                }
            }

        } break;
        
    };

    if (state == State::Error)
        return {state, current_file_size, bytes_remaining, error_message};
    else
        return {state, current_file_size, bytes_remaining};
}


// reads from disk to RAM
bool FirmwareUpdater::start_reading_file() {
    auto size = manifest.files[current_file_idx].filesize;

    if (current_file_idx == 0)
        file_images[current_file_idx] = {(char *)ram_buffer.data(), size};
    else
        file_images[current_file_idx] = std::span<char>{
            file_images[current_file_idx - 1].data() + file_images[current_file_idx - 1].size(), size};

    pr_trace("A7: request to load %s to 0x%x\n",
                manifest.files[current_file_idx].filename.c_str(),
                file_images[current_file_idx].data());

    auto success = file_storage.request_load_file(
            manifest.files[current_file_idx].filename, vol, file_images[current_file_idx]);

    return success;
}

// writes from RAM to flash/wifi-uart
bool FirmwareUpdater::start_writing_file()
{
    auto& thisFileImage = file_images[current_file_idx];

    int file_size = thisFileImage.size();
    auto &cur_file = manifest.files[current_file_idx];

    switch (cur_file.type) {

        case UpdateType::App:
            current_file_loader = std::make_unique<FirmwareFlashLoader>(thisFileImage);
            break;

        case UpdateType::Wifi:
            current_file_loader = std::make_unique<FirmwareWifiLoader>(thisFileImage);
            break;
            
        default:
            current_file_loader.reset();
            pr_err("Invalid update file type\n");
            break;
    }

    if (current_file_loader)
    {
        if (current_file_loader->verify(cur_file.md5))
        {
            if (current_file_loader->start())
            {
                moveToState(State::Writing);
                current_file_size = file_size;
                return true;
            }
            else
            {
                abortWithMessage("Could not start writing application firmware to flash");
            }
        }
        else
        {
            abortWithMessage("App firmware file not valid");
        }
    }

    return false; 
}

void FirmwareUpdater::abortWithMessage(const char* message)
{
    state = State::Error;
    error_message = message;
}

void FirmwareUpdater::moveToState(State newState)
{
    pr_trace("Update move start %u -> %u\n", state, newState);
    state = newState;
}


}