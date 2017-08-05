#pragma once 
#include <ui/shell_command.h>

namespace ui {
    namespace commands {
        class dir_command : public shell_command {
        public:
            dir_command() : shell_command("dir", "list all the files in the directory") {}
            virtual void run(const char* argument);
        };
    }
}