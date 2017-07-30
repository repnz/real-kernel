#include "os\console.h"
#include "str_tools.h"
#include "bios\keyboard.h"
#include "bios\video.h"
#include "bios\disk.h"
#include "system\interrupts.h"
#include "system\apm.h"

using namespace os;
using namespace bios;
using namespace system;

#define ECHO_COMMAND "echo"
#define EXIT_COMMAND "exit"

void shell() {
	console::clear();

	console::print_string("Welcome to Ori's Shell!\r\n");

	char command[42];
	bool running = true;

	while (running) {
		console::print_string(">> ");
		word in = console::read_line(command, 40);
		console::print_line();
		console::print_mem((byte*)command, in);

		if (in == 0) {
			continue;
		}

		if (str_tools::equals_length(command, EXIT_COMMAND, sizeof(EXIT_COMMAND))) {

			console::print_string("bye!");
			keyboard::read_press_scan_code();
			running = false;

		} else if (str_tools::equals_length(command, ECHO_COMMAND, sizeof(ECHO_COMMAND))) {
			console::print_string(command + sizeof(ECHO_COMMAND));
			console::print_line();

		} else {
			console::print_string("Unknown command ");
			console::print_string(command);
			console::print_line();
		}
	}
}

void power_off() {
	byte result_code = apm::installation_check();

	if (!result_code) {
		return;
	}

	console::print_string("apm is installed!\r\n");

	result_code = apm::disconnect();

	if (!(result_code == apm::SUCCESS || result_code == apm::INTERFACE_NOT_CONNECTED)) {
		return;
	}
	
	console::print_string("connection is disconnected for sure\r\n");

	result_code = apm::connect();

	if (!result_code) {
		return;
	}

	console::print_string("connected to apm interface..\r\n");

	if (!apm::set_management_enabled(true)) {
		return;
	}

	console::print_string("power management enabled..\r\n");

	apm::set_power_state(apm::power_states::off);		
}

extern "C" void kernel_main() {
	shell();
	power_off();
}