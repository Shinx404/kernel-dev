EXTERN kernel_main
BITS 16
ORG 0x7c00

%include "gdt.asm"

CALL setGdt

032 MOV eax, cr0
032 OR eax, 1
032 MOV cr0, eax
JMP 0x08:protected_mode

BITS 32

protected_mode:
	MOV ax, 0x10
	MOV ds, ax
	MOV es, ax
	MOV ss, ax
	MOV fs, ax	
	MOV gs, ax
	CALL kernel_main

times 510 - ($ - $$) db 0
dw 0xAA55

