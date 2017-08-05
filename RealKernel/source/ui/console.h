#pragma once
#include <bios/video.h>
#include <std/inta.h>

namespace ui
{
	namespace console 
	{
		void clear();

		void print_char(char c);

		void print_line();

		void print_string(const char* str);

		void print_string(const char* str, word len);

		void print_hex(word w, byte bytes = 1);

		void print_mem(byte* b, word len);

		word read_line(char* buffer, word len);
		
	}
}