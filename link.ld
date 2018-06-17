ENTRY(start)
OUTPUT_FORMAT(elf32-i386)
phys = 0x00100000;
SECTIONS
{
	.text phys : AT(phys)
	{
		code = .; _code = .; __code = .;
		*(.text)		/* all text sections from all files */
		. = ALIGN(4096);
	}
	
	.data : AT(phys + (data - code))
	{
		data = .; _data = .; __data = .;
		*(.data)		/* all data sections from all files */
		*(.rodata)		/* all read-only data sections from all files */
		. = ALIGN(4096);
	}
	
	.bss : AT(phys + (bss - code))
	{
		bss = .; _bss = .; __bss = .;
		*(.bss)			/* all bss sections from all files */
		. = ALIGN(4096);
	}
	
	end = .; _end = .; __end = .;

}
