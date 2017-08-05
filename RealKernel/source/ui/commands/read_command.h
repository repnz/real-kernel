#pragma once
#include <ui/shell_command.h>

namespace ui {
    namespace commands {
        class read_command : public shell_command {
        public:
            read_command() : shell_command("read", "read and print the contents of a file") {}
            virtual void run(const char* argument);
        };
    }
}