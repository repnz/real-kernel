#include <bios\keyboard.h>

namespace bios {
	namespace keyboard {
		press_info read_press() {
			byte scanCode;
			char character;
			
			__asm {
				mov ah, 0
				int 16h
				mov scanCode, ah
				mov character, al
			}

			
			press_info i;

			i.scanCode = scanCode;
			i.asciiChar = character;
			return i;
		}

		char read_press_char() {
			char res;

			__asm {
				mov ah, 0
				int 16h
				mov res, al
			}

			return res;
		}

		byte read_press_scan_code() {
			byte res;

			__asm {
				mov ah, 0
				int 16h
				mov res, ah
			}

			return res;
		}
	}
}