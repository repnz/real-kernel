#pragma once
#include <ui/shell_command.h>

namespace ui {
	namespace commands {
		class echo_command : public shell_command {
		public:
			echo_command() : shell_command("echo", "print argument to the console") {}
			virtual void run(const char* argument);
		};
	}
}