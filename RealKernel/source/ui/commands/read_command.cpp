#include <ui/commands/read_command.h>
#include <file_system/directory.h>
#include <ui/console.h>

using namespace file_system;

void ui::commands::read_command::run(const char* argument) {
    
    file f = file::open(argument);
    
    byte buffer[1024];
    word bytesRead;

    while ((bytesRead = f.read(buffer, 1024)) > 0) {
        console::print_string((const char*)buffer, bytesRead);
    }
}