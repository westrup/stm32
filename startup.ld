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
    flash_start_data = .;
  } >FLASH

  .data : {
    ram_start_data = .;
    * (.data*);
    ram_end_data = .;
  } >RAM AT >FLASH

  .bss : {
    start_bss = .;
    * (.bss*);
    * (COMMON);
    end_bss = .;
  } >RAM
}
