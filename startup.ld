MEMORY {
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}

ENTRY (reset_handler);

SECTIONS {
  .text : {
    KEEP(* (vectors));
    * (.text*);
  } >FLASH

  .rodata : {
    * (.rodata*);
  } >FLASH

  .data : {
    * (.data*);
  } >RAM AT >FLASH

  .bss : {
    * (.bss*);
    * (COMMON);
  } >RAM
}
