#include "updater.hh"
#include "loaders/flash/firmware_flash_loader.hh"
#include "loaders/wifi/firmware_wifi_loader.hh"

namespace MetaModule
{

FirmwareUpdater::FirmwareUpdater(FileStorageProxy &file_storage)
    : file_storage{file_storage}
    , state(State::Idle)
    , current_file_idx(0)
    , current_file_size(0)
    , file_requested(false) {
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

            if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {

                auto parseResult = parser.parse(manifest_buffer);

                if (parseResult and parseResult->files.size() > 0) {
                    manifest = *parseResult;

                    current_file_idx = 0;
                    file_requested = false;
                    file_images.reserve(manifest.files.size());
                    
                    moveToState(State::LoadingFilesToRAM);

                } else {
                    abortWithMessage("Manifest file is invalid");
                }

            } else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
                abortWithMessage("Failed reading manifest file");
            }

        } break;

        case LoadingFilesToRAM: {
            if (!file_requested)
                start_reading_file();
            else
                check_reading_done();

            if (current_file_idx >= manifest.files.size())
            {
                // Write first file
                current_file_idx = 0;
                current_file_size = start_writing_file();
            }

        } break;

        case Writing: {
            auto [bytes_rem, err] = current_file_loader->load_next_block();

            if (err == FileLoaderBase::Error::Failed) {
                bytes_remaining = bytes_rem;
                abortWithMessage("Failed writing app to flash");

            } else if (bytes_rem > 0) {
                bytes_remaining = bytes_rem;

            } else {

                // write next file
                current_file_idx++;
                current_file_size = start_writing_file();
            }

        } break;
        
    };

    if (state == State::Error)
        return {state, current_file_size, bytes_remaining, error_message};
    else
        return {state, current_file_size, bytes_remaining};
}


// reads from disk to RAM
void FirmwareUpdater::start_reading_file() {
    auto size = manifest.files[current_file_idx].filesize;

    if (current_file_idx == 0)
        file_images[current_file_idx] = {(char *)ram_buffer.data(), size};
    else
        file_images[current_file_idx] = std::span<char>{
            file_images[current_file_idx - 1].data() + file_images[current_file_idx - 1].size(), size};

    pr_trace("A7: request to load %s to 0x%x\n",
                manifest.files[current_file_idx].filename.c_str(),
                file_images[current_file_idx].data());

    if (file_storage.request_load_file(
            manifest.files[current_file_idx].filename, vol, file_images[current_file_idx]))
    {
        file_requested = true;
    } else {
        abortWithMessage("Failed to request firmware file");
    }
}

void FirmwareUpdater::check_reading_done() {
    auto message = file_storage.get_message();

    if (message.message_type == FileStorageProxy::LoadFileToRamSuccess) {
        pr_trace("A7: file loaded\n");
        current_file_idx++;
        file_requested = false;

    } else if (message.message_type == FileStorageProxy::LoadFileToRamFailed) {
        abortWithMessage("Failed to load a firmware file");
    }
}

// writes from RAM to flash/wifi-uart
int FirmwareUpdater::start_writing_file()
{
    if (current_file_idx > manifest.files.size())
    {
        moveToState(State::Success);
        return 0;
    }
    else {

        int file_size = file_images[current_file_idx].size();
        auto &cur_file = manifest.files[current_file_idx];

        switch (cur_file.type) {

            case UpdateType::App:
                current_file_loader = std::make_unique<FirmwareFlashLoader>(file_images[current_file_idx]);
                break;

            case UpdateType::Wifi:
                current_file_loader = std::make_unique<FirmwareWifiLoader>(file_images[current_file_idx]);
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

        return file_size;
    }
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