ENTRY(start)

INPUT(boot.o kernel.o)

SECTIONS
{
	. = 0x7C00;

	.text : {*(.text)}
	.data : {*(.data)}
	.bss : {*(.bss)}

}


