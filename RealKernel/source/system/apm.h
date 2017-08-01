#pragma once
#include <stdint.h>

namespace system {

	namespace apm {

		typedef word apm_flag;

		namespace apm_flags {
			const apm_flag protected_mode_16_supported = 0x1;
			const apm_flag protected_mode_32_supported = 0x2;
			const apm_flag cpu_idle_slows = 0x3;
			const apm_flag apm_disabled = 0x4;
			const apm_flag apm_disengaged = 0x5;
		}

		struct apm_info {
			byte major_revision;
			byte minor_revision;
			word flags;
		};

		const byte success = 0x1;
		const byte apm_supported = 1;
		const byte unrecognized_device_id = 9;
		const byte apm_not_present = 0x86;

		const byte real_mode_established = 0x2;
		const byte protected_mode_16_established = 0x5;
		const byte protected_mode_32_established = 0x7;

		const byte power_management_disabled = 1;
		const byte parameter_out_of_range = 0xa;
		const byte interface_not_engaged = 0xb;
		const byte unable_to_enter_state = 0x60;
		const byte interface_not_connected = 0x3;

		typedef byte power_state;

		namespace power_states {
			const power_state apm_enabled = 0x0;
			const power_state standby = 0x1;
			const power_state suspend = 0x2;
			const power_state off = 0x3;
		}

		typedef byte mode;

		const mode real = 1;
		const mode protected_16 = 2;
		const mode protected_32 = 3;


		byte connect();
		byte disconnect();
		byte set_power_state(power_state state);
		byte set_management_enabled(bool enabled);
		byte installation_check(apm_info* info = nullptr);

	}
}