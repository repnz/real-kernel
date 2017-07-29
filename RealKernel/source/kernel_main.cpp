#include "os\console.h"
#include "bios\keyboard.h"
#include "bios\video.h"
#include "bios\disk.h"

using namespace os;

extern "C" void kernel_main() {

	console::print_string("Hello From Kernel Code!");

	char value = bios::keyboard::read_press_char();

	console::print_char(value);

}