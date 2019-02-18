OUTPUT_FORMAT("binary")
bootloader_address = 0x00007c00;
kernel_start_address = 0x8000;

SECTIONS
{
  .bootloader : AT(0x00007c00) {
	code = .;
	boot.o(.text)
	. = ALIGN(512)
  }
  
  .text phys : AT(kernel_start_address) {
    code = .;
    *(.text)
    *(.rodata)
    . = ALIGN(4096);
  }
  .data : AT(kernel_start_address + (data - code))
  {
    data = .;
    *(.data)
    . = ALIGN(4096);
  }
  
  .bss : AT(phys + (bss - code))
  {
    bss = .;
    *(.bss)
    . = ALIGN(4096);
  }
  end = .;
}