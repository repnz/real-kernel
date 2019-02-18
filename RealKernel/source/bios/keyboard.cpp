#include <bios/keyboard.h>

namespace bios {
	namespace keyboard {
		press_info read_press() {
            byte scanCode = 0;
            char character = 0;
			
            asm(
                "mov ah, 0;"
                "int 0x16;"
                "mov scanCode, ah;"
                "mov character, al;"
                );

            press_info i;
            i.scanCode = scanCode;
            i.asciiChar = character;
			return i;
		}

		char read_press_char() {
            char res = 0;

            asm(
                "mov ah, 0;"
                "int 0x16;"
                "mov res, al;"
                );

			return res;
		}

		byte read_press_scan_code() {
            byte res = 0;

            asm(
                "mov ah, 0;"
                "int 0x16;"
                "mov res, ah;"
                );

			return res;
		}
	}
}