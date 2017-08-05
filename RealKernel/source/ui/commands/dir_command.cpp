#include <ui/commands/dir_command.h>
#include <ui/console.h>
#include <file_system/directory.h>

void ui::commands::dir_command::run(const char* argument) {
    file_system::directory* directory = file_system::directory::get_directory();

    for (word i = 0; i < file_system::max_files; ++i) {
        const file_system::file_data* file = &directory->files[i];

        if (!file->is_used) {
            continue;
        }

        console::print_string(file->name);
        console::print_string("   0x");
        console::print_hex(file->length);
        console::print_string(" bytes\r\n");
    }
}