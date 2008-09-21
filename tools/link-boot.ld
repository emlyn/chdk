
ENTRY(_start)

SECTIONS
{

    .text : {
	link_text_start = .;
	_start = .;
	*(.entry)
	*(.text) *(.glue_7t) *(.glue_7)
	*(.rodata)
	*(.rdata)
	*(.blob*)
	. = ALIGN(4);
    }
    . = ALIGN(4);
    link_text_end = .;


    .data : {
	link_data_start = .;
	*(.data)
	. = ALIGN(4);
    }
    . = ALIGN(4);
    link_data_end = .;


    .bss : {
	link_bss_start = .;
	*(.bss) *(COMMON)
	. = ALIGN(16);
	_end = .;
    }
    . = ALIGN(16);
    link_bss_end = .;

}

