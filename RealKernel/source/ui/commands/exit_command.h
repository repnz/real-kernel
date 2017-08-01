#pragma once 
#include <ui/shell_command.h>

namespace ui {
	namespace commands {

		class exit_command : public shell_command {
		public:
			exit_command() : shell_command("exit", "power off the shell") {}
			virtual void run(const char* argument);
		};
	}
}