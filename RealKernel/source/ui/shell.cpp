#include <ui/shell.h>
#include <ui/console.h>
#include <std/str.h>

namespace ui {
	shell::shell() : _nextCommandIndex(0) {
	}

	void shell::run() {
		console::clear();
		console::print_string("Welcome to Ori's Shell!\r\n");

		char userInput[42];
		bool running = true;

		while (running) {
			console::print_string(">> ");
			word in = console::read_line(userInput, 40);
			console::print_line();

			if (in == 0) {
				continue;
			}

			byte i;

			for (i = 0; i < _nextCommandIndex; ++i){
				register shell_command* cmd = _commands[i];

				if (std::str_tools::equals_until(cmd->name(), userInput, ' ')) {
					_commands[i]->run(userInput + cmd->nameLength()+1);
					break;
				}
			}

			if (i == _nextCommandIndex) {
				console::print_string("Unknown command ");
				console::print_string(userInput);
				console::print_line();
			}
		}
	}

	void shell::add_command(shell_command* cmd) {
		cmd->set_shell(this);
		_commands[_nextCommandIndex] = cmd;
		++_nextCommandIndex;
	}
}
