#include <ui/shell.h>
#include <ui/commands/echo_command.h>
#include <ui/commands/exit_command.h>
#include <ui/commands/help_command.h>

using namespace ui;

extern "C" void kernel_main() {
	
	commands::echo_command echo;
	commands::exit_command exit;
	commands::help_command help;

	shell s;
	
	s.add_command(&echo);
	s.add_command(&exit);
	s.add_command(&help);

	s.run();
}