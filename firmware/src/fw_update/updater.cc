#include "updater.hh"
#include "loaders/flash/firmware_flash_loader.hh"
#include "loaders/flash/firmware_flash_verifier.hh"
#include "loaders/wifi/firmware_wifi_loader.hh"
#include "loaders/wifi/firmware_wifi_verifier.hh"
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
    std::size_t bytes_completed = 0;

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
                    // Proceed with first file
                    current_file_idx = 0;
                    moveToState(StartVerify);
                }
            }
            else if (message.message_type == FileStorageProxy::LoadFileToRamFailed)
            {
                abortWithMessage("Failed to load a firmware file");
            }

        } break;

        case StartVerify:
        {
            auto success = start_verifying_file();
            if (success)
            {
                current_file_size = file_images[current_file_idx].size();
                moveToState(Verifying);
            }
            else
            {
                abortWithMessage("Cannot start verifying file");
            }
        } break;

        case Verifying:
        {
            auto [bytes_cmp, err] = current_file_loader->process();
            bytes_completed = bytes_cmp;

            if (err == FileWorkerBase::Error::Failed)
            {
                abortWithMessage("Verification failed");
            }
            else if (err == FileWorkerBase::Error::Mismatch)
            {
                moveToState(StartWriting);
            }
            else if (bytes_completed == current_file_size)
            {
                if (current_file_idx < manifest.files.size()-1)
                {
                    // proceed with next file
                    current_file_idx++;
                    moveToState(StartVerify);
                }
                else
                {
                    moveToState(Success);
                }
            }
            
        } break;

        case StartWriting:
        {
            auto success = start_writing_file();
            if (success)
            {
                current_file_size = file_images[current_file_idx].size();
                moveToState(Writing);
            }
            else
            {
                abortWithMessage("Cannot start writing file");
            }

        } break;

        case Writing: {
            auto [bytes_cmp, err] = current_file_loader->process();

            if (err == FileWorkerBase::Error::Failed)
            {
                bytes_completed = bytes_cmp;
                abortWithMessage("Failed writing app to flash");
            }
            else if (bytes_cmp < current_file_size)
            {
                bytes_completed = bytes_cmp;
            }
            else
            {
                if (current_file_idx < manifest.files.size()-1)
                {
                    // proceed with next file
                    current_file_idx++;
                    moveToState(StartVerify);
                }
                else
                {
                    moveToState(Success);
                }
            }

        } break;
        
    };

    if (state == State::Error)
        return {state, current_file_size, bytes_completed, error_message};
    else
        return {state, current_file_size, bytes_completed};
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

    auto &cur_file = manifest.files[current_file_idx];

    switch (cur_file.type) {

        case UpdateType::App:
            current_file_loader = std::make_unique<FirmwareFlashLoader>(thisFileImage, 0);
            break;

        case UpdateType::Wifi:
            current_file_loader = std::make_unique<FirmwareWifiLoader>(thisFileImage, 0);
            break;
            
        default:
            current_file_loader.reset();
            pr_err("Invalid update file type\n");
            break;
    }

    if (current_file_loader)
    {
        return current_file_loader->start() == FileWorkerBase::Error::None;
    }

    return false; 
}

bool FirmwareUpdater::start_verifying_file()
{
    auto& thisFileImage = file_images[current_file_idx];

    auto &cur_file = manifest.files[current_file_idx];

    switch (cur_file.type) {

        case UpdateType::App:
            current_file_loader = std::make_unique<FirmwareFlashVerifier>(thisFileImage, cur_file.md5, 0);
            break;

        case UpdateType::Wifi:
            current_file_loader = std::make_unique<FirmwareWifiVerifier>(thisFileImage, cur_file.md5, 0);
            break;
            
        default:
            current_file_loader.reset();
            pr_err("Invalid update file type\n");
            break;
    }

    if (current_file_loader)
    {
        return current_file_loader->start() == FileWorkerBase::Error::None;
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