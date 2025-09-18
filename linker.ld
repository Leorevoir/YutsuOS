ENTRY(_start)

SECTIONS
{
  . = 1M;

  .multiboot : {
    KEEP(*(.multiboot))
  }

  .text : {
    *(.text*)
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    *(.bss*)
    *(COMMON)
  }

  /DISCARD/ : { *(.eh_frame*) }
}
