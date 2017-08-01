#include <ui/commands/help_command.h>
#include <ui/console.h>

namespace ui {
	namespace commands {
		void help_command::run(const char* argument) {

			for (byte i = 0; i < shell().command_count(); ++i) {
				shell_command* cmd = shell().get_command(i);

				console::print_string("     ");
				console::print_string(cmd->name());
				console::print_string("    ->     ");
				console::print_string(cmd->description());
				console::print_line();
			}

		}
	}
}