#pragma once
#include <stdint.h>
#include <lib/str_tools.h>
#include <ui/shell_command.h>

namespace ui {
	const byte number_of_commands = 20;

	class shell_command;

	class shell {
	private:
		
		shell_command* _commands[number_of_commands];
		byte _nextCommandIndex;
	public:
		shell();
		
		byte command_count() const {
			return _nextCommandIndex;
		}

		shell_command* get_command(byte index) {
			if (index >= 0 && index < _nextCommandIndex) {
				return _commands[index];
			}

			return nullptr;
		}

		void add_command(shell_command* cmd);
		void run();
	};


}