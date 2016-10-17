MEMORY {
  LORAM (rw)      : ORIGIN = 0x00000000, LENGTH = 0x00020000
  BOOTROM (rx)    : ORIGIN = 0x00020000, LENGTH = 0x00040000
  HIRAM (rw)      : ORIGIN = 0x00060000, LENGTH = 0x00F90000
}

stack_size = 32 * 256;  /* DUCKY_STACK_SIZE */

_stack_start = ORIGIN(BOOTROM);
_stack_end = ORIGIN(BOOTROM) - stack_size;

SECTIONS {
  /DISCARD/ : {
    /* drop .text.entry from libducky's crt0.o */
    *(.text.entry)
  }

  . = 0x00020000;

  .text : {
    . = ALIGN(4);
    _text_start = .;
    KEEP(*(.text.boot))
    *(.text)
    *(.text*)
    _text_end = .;
  }

  .rodata : {
    . = ALIGN(4);
    _rodata_start = .;
    *(.rodata)
    *(.rodata*)
    _rodata_end = .;
  } >BOOTROM

  . = 0x00060000;

  _hiram_start = .;

  /* .data section LMA is right after .rodata but its VMA must be in RAM. Copying the data from ROM
   * to the RAM is handled by __init_data function */
  .data : AT ( ADDR(.rodata) + SIZEOF(.rodata) ) {
    . = ALIGN(4);
    _data_start = .;
    *(.data)
    *(.data*)
    _data_end = .;
  } >HIRAM

  /* .bss may lie right after .data VMA */
  .bss : AT (0x00060000 + SIZEOF(.mdata) ) {
    . = ALIGN(4);
    _bss_start = .;
    *(.bss)
    *(.bss*)
    _bss_end = .;
  } >HIRAM

  /* heap is the rest */
  .heap : AT (0x00060000 + SIZEOF(.mdata) + SIZEOF(.bss) ) {
    . = ALIGN(4);
    _heap = .;
  } >HIRAM
}
