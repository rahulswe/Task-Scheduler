ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 512K
	SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128K /* SRAM1 + SRAM2 */
	/* SRAM1(rwx) : ORIGIN = 0x20000000, LENGTH = 112K
	SRAM2(rwx) : ORIGIN = 0x20000000 + 112K - 1 ??, LENGTH = 16K */
}


SECTIONS
{
	.text :
	{
	    /* .__stext = VMA = FLASH Starting Address // Note location counter (.) always tracks the VMA */
		*(.isr_vector)
		*(.text)
		*(.text.*)
		*(.init) /* not really required to combine it under this text section */
		*(.fini) /* not really required to combine it under this text section */
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		__etext = .;
	} > FLASH AT> FLASH /* since LMA=VMA=FLASH, it can also be written as "} > FLASH" */

	__la_data = LOADADDR(.data);
	.data :
	{
		__sdata = .;
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		__edata = .;
	} > SRAM AT> FLASH

	.bss :
	{
		__sbss = .;
		__bss_start__ = __sbss;
		*(.bss)
		*(.bss.*)
		. = ALIGN(4);
		__ebss = .;
		__bss_end__ = __ebss;
		/* . = ALIGN(4);*/
		__end__ = .;
		end = .; /* this marks end of heap as required for __sbrk function in syscalls.c. For now keep it = start of heap = end of bss, from where the heap section starts, later memory management function will update this symbol to understand whether more memory can be allocated or not */
	} > SRAM AT> SRAM /* there is no LMA for this section */
}