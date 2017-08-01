#pragma once 
#include <ui/shell_command.h>

namespace ui {
	namespace commands {
		class help_command : public shell_command {
		public:
			help_command() : shell_command("help", "print commands help") {}
			virtual void run(const char* argument);
		};
	}
}