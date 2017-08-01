#include <system/apm.h>

namespace system {
	namespace apm {

		byte installation_check(apm_info* info) {
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
					mov byte ptr[bx], ah   // major revision
					mov byte ptr[bx + 1], al // minor revision
					mov word ptr[bx + 2], cx   // flags
				return_result:
			}

			return result_code;
		}

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
				return_result :
			}

			return result_code;
		}


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
				return_result :
			}

			return result_code;
		}

		byte set_management_enabled(bool enabled) {
			byte result = apm::success;

			__asm {
				mov ah, 53h
					mov al, 08h
					mov bx, 1
					xor ch, ch
					mov cl, enabled
					int 15h
					jnc return_result
					mov result, ah
				return_result :
			}

			return result;
		}
	}
}