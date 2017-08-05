#pragma once
#include <std/inta.h>
#include <file_system/file_data.h>
#include <file_system/file.h>

namespace file_system {

    const byte max_files = 7;

    struct directory {
        file_system::file_data files[max_files];

        static directory* get_directory();
        static file_data* get_file_data(const char* fileName);
    };

    
}