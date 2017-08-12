#include <bios\keyboard.h>

namespace bios {
	namespace keyboard {
		press_info read_press() {
			byte scanCode;
			char character;
			
            asm(
                "mov ah, 0;"
                "int 0x16;"
                "mov scanCode, ah;"
                "mov character, al;"
                );

			return i;
		}

		char read_press_char() {
			char res;

            asm(
                "mov ah, 0;"
                "int 0x16;"
                "mov res, al;"
                );

			return res;
		}

		byte read_press_scan_code() {
			byte res;

            asm(
                "mov ah, 0;"
                "int 0x16;"
                "mov res, ah;"
                );

			return res;
		}
	}
}