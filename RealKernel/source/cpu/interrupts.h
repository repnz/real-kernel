#pragma once

namespace cpu {

	namespace interrupts {
		inline void enable() {
			__asm  {
				sli
			}
		};

		inline void disable() {
			__asm {
				cli
			}
		}
	}
}