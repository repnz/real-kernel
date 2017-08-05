#pragma once
#include <std/inta.h>
#include <std/str.h>
#include <ui/shell.h>

namespace ui {

	class shell;

	class shell_command {
	private:
		const char* _name;
		const char* _description;
		word _nameLength;
		shell* _shell;
	protected:
		shell& get_shell() {
			return *_shell;
		}
	public:
		shell_command(const char* name, const char* description) :
			_name(name),
			_nameLength(std::str_tools::length(_name)),
			_description(description) {
		}

		void set_shell(ui::shell* s) { _shell = s; }
		const char* name() const { return _name; }
		const char* description() const { return _description; }
		word nameLength() const { return _nameLength; }
		virtual void run(const char* argument) = 0;
	};
}
