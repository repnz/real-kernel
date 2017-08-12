#include <file_system/directory.h>
#include <bios/disk.h>
#include <std/str.h>

namespace file_system {
    
    
    static bool initialized = false;
    static directory _directory;

    byte directory_start_sector = 10;
    byte directory_sectors_size = sizeof(directory);

    directory* directory::get_directory() {
        if (initialized) {
            return &_directory;
        }
        
        
        byte sectorsRead;

        if (bios::disk::read_sectors(
            0x80,
            (byte*)&_directory,
            0,
            file_system::directory_start_sector,
            0,
            file_system::directory_sectors_size,
            &sectorsRead
            ) != bios::disk::operation_codes::success) {
            return nullptr;
        }

        return &_directory;
    }

    file_data* directory::get_file_data(const char* fileName) {

        directory::get_directory();

        for (byte i = 0; i < file_system::max_files; ++i) {

            file_data* f = &_directory.files[i];

            if (f->is_used && std::str_tools::equals(f->name, fileName)) {
                return f;
            }

        }

        return nullptr;

    }
}