OUTPUT_FORMAT("binary")
STARTUP(Boot.o)
phys = 0x7c00;
SECTIONS
{
  .text.bootloader {
    bootloader.o(.text)
    .ALIGN = 512
  }

  .text.kernel : AT(phys + (data - code))
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