#include <system/apm.h>

namespace system {
	namespace apm {

		byte installation_check(apm_info* info) {
            byte result_code;

            asm(
                "mov ah, 0x53;" // apm command
                "mov al, 0x00;" // installation check command
                "xor bx, bx;"
                "int 0x15;"
                "mov result_code, ah;"
                "jnc return_result_1;"
                "mov byte ptr result_code, 1;"
                "mov bx, info;"
                "test bx, bx;"
                "jz return_result_1;"
                "mov byte ptr [bx], ah;" // major revision
                "mov byte ptr [bx + 1], al;" // minor revision
                "mov word ptr [bx + 2], cx;" // flags
            );

        return_result_1:
			return result_code;
		}

		byte connect() {
			byte result = 1;

            asm(
                "mov ah, 0x53;" // apm command
                "mov al, 0x01;" // connect command
                "xor bx, bx;"
                "int 0x15;"
                "jnc return_result2;"
                "mov result, ah;" // set to error
                );

        return_result2:

			return result;
		}

		byte disconnect() {
            byte result_code = 1;

            asm(
                "mov ah, 0x53;"
                "mov al, 0x04;"
                "xor bx, bx;"
                "int 0x15;"
                "jnc return_result_3;" // success
                "mov result_code, ah;"
                );

        return_result_3:
			return result_code;
		}


		byte set_power_state(power_state state) {
            byte result_code = 1;

            asm(
                "mov ah, 0x53;"
                "mov al, 0x07;"
                "mov bx, 1;"
                "xor ch, ch;"
                "mov cl, state;"
                "int 0x15;"
                "jnc return_result_4;"
                "mov result_code, ah;"
                );

        return_result_4:
			return result_code;
		}

		byte set_management_enabled(bool enabled) {
			byte result = apm::success;

            asm(
                "mov ah, 0x53;"
                "mov al, 0x08;"
                "mov bx, 1;"
                "xor ch, ch;"
                "mov cl, enabled;"
                "int 0x15;"
                "jnc return_result;"
                "mov result, ah;"
                "return_result :;"
                );

			return result;
		}
	}
}