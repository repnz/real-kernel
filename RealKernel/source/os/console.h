#pragma once
#include "types.h"

namespace os 
{
	namespace console 
	{
		void print_char(char c);

		void print_line();

		void print_string(const char* str);

		void print_string(const char* str, word len);

		void print_hex(word w, byte bytes = 1);

		void print_mem(byte* b, word len);

		
	}
}