#include <ui/commands/echo_command.h>
#include <ui/console.h>

namespace ui {
	namespace commands {
		void echo_command::run(const char* argument) {
			console::print_string(argument);
			console::print_line();
		}
	}
}