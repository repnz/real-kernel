#pragma once
#include "types.h"

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

	const byte SUCCESS = 0x1;

	const byte APM_SUPPORTED = 1;
	const byte UNRECOGNIZED_DEVICE_ID = 9;
	const byte APM_NOT_PRESENT = 86;
	
	byte installation_check(apm_info* info = nullptr) {
		byte result_code;

		__asm {
			mov ah, 53h // apm command
			mov al, 00h // installation check command
			xor bx, bx
			int 15h
			mov result_code, ah
			jnc return_result
			mov result_code, 1
			mov bx, info
			test bx, bx
			jz return_result

			// initialize the apm info 
			mov byte ptr [bx], ah   // major revision
			mov byte ptr [bx+1], al // minor revision
			mov word ptr [bx+2], cx   // flags
		return_result:
		}

		return result_code;
	}

	typedef byte mode;

	const mode real = 1;
	const mode protected_16 = 2;
	const mode protected_32 = 3;
	

	const byte REAL_MODE_ESTABLISHED = 0x2;
	const byte PROTECTED_MODE_16_ESTABLISHED = 0x5;
	const byte PROTECTED_MODE_32_ESTABLISHED = 0x7;
	

	byte connect() {
		byte result = 1;

		__asm {
			mov ah, 53h // apm command
			mov al, 01h // connect command
			xor bx, bx
			mov result, 1 // default success
			int 15h
			jnc return_result
			mov result, ah // set to error
		return_result:
		}

		return result;
	}

	const byte INTERFACE_NOT_CONNECTED = 0x3;

	byte disconnect() {
		byte result_code;

		__asm {
			mov ah, 53h
			mov al, 04h
			xor bx, bx
			int 15h
			mov result_code, 1
			jnc return_result // success
			mov result_code, ah
		return_result:
		}

		return result_code;
	}


	typedef byte power_state;

	namespace power_states {
		const power_state apm_enabled = 0x0;
		const power_state standby = 0x1;
		const power_state suspend = 0x2;
		const power_state off = 0x3;
	}

	const byte power_management_disabled = 1;
	const byte interface_not_connected = 3;
	const byte parameter_out_of_range = 0xa;
	const byte interface_not_engaged = 0xb;
	const byte unable_to_enter_state = 0x60;

	byte set_power_state(power_state state) {
		byte result_code;

		__asm {
			mov ah, 53h
			mov al, 07h
			mov bx, 1
			xor ch, ch
			mov cl, state
			mov result_code, 1
			int 15h
			jnc return_result
			mov result_code, ah
		return_result:
		}

		return result_code;
	}

	byte set_management_enabled(bool enabled) {
		byte result = SUCCESS;

		__asm {
			mov ah, 53h
			mov al, 08h
			mov bx, 1
			xor ch, ch
			mov cl, enabled
			int 15h
			jc return_result
			mov result, ah
		return_result:
		}
	}


}