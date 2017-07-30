#pragma once
#include "types.h"

namespace system {

	namespace interrupts {
		inline void enable() {
			__asm  {
				sti
			}
		};

		inline void disable() {
			__asm {
				cli
			}
		}

		struct ivt_entry {
			word segment;
			word offset;
		};

		class ivt {
		private:
			ivt_entry* entries;
		public:
			ivt() {
				entries = (ivt_entry*)0;
			}

			ivt_entry* get_entry(byte index) { return (entries + index); }
		};
	}
}