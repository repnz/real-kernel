#include <stdint.h>
#include <ui/commands/exit_command.h>
#include <ui/console.h>
#include <system/apm.h>

using namespace system;

namespace ui {
	namespace commands {

		void exit_command::run(const char* argument) {

			byte result_code = apm::installation_check();

			if (result_code != apm::success) {
				console::print_string("exit error: apm is not installed!\r\n");
				return;
			}


			result_code = apm::disconnect();

			if (!(result_code == apm::success || result_code == apm::interface_not_connected)) {
				console::print_string("cannot disconnect from apm interface!\r\n");
				return;
			}

			result_code = apm::connect();

			if (result_code != apm::success) {
				console::print_string("could not connect to apm interface!\r\n");
				return;
			}

			result_code = apm::set_management_enabled(true);

			if (result_code != apm::success) {
				console::print_string("could not enable power management!\r\n");
				return;
			}

			if (apm::set_power_state(apm::power_states::off) != apm::success) {
				console::print_string("cannot power off system\r\n");
			}
		}
	}
}