#include <ui/shell.h>
#include <ui/commands/echo_command.h>
#include <ui/commands/exit_command.h>
#include <ui/commands/help_command.h>
#include <ui/commands/dir_command.h>
#include <file_system/file.h>
#include <ui/console.h>

using namespace ui;

extern "C" void kernel_main() {
    console::clear();
    console::print_string("hello");

	commands::echo_command echo;
	commands::exit_command exit;
	commands::help_command help;
    commands::dir_command dir;
	shell s;
	
	s.add_command(&echo);
	s.add_command(&exit);
	s.add_command(&help);
    s.add_command(&dir);

	s.run();
}
