EXTERN kernel_main
BITS 16
%include "gdt.asm"

start:
	
	CALL setGdt
	o32 MOV eax, cr0
	o32 OR eax, 1
	o32 MOV cr0, eax
	JMP 0x08:protected_mode
	
times 510 - ($ - $$) db 0
dw 0xAA55

BITS 32

protected_mode:
	MOV ax, 0x10
	MOV ds, ax
	MOV es, ax
	MOV ss, ax
	MOV fs, ax	
	MOV gs, ax
	CALL kernel_main

