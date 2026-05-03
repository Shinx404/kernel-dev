BITS 16
ORG 0x7C00

start:
	jmp boot

gdt_start:
    dq 0

gdt_code:
    dw 0xFFFF
    dw 0
    db 0
    db 0x9A
    db 0xCF
    db 0

gdt_data:
    dw 0xFFFF
    dw 0
    db 0
    db 0x92
    db 0xCF
    db 0
gdt_end:

gdtr:
    dw gdt_end - gdt_start - 1
    dd gdt_start

boot:
	MOV sp, 0x7C00
	XOR ax, ax
	MOV ds, ax	
	lgdt [gdtr]
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
	MOV esp, 0x90000
	MOV fs, ax	
	MOV gs, ax
	MOV byte [0xB8000], 'A'
	MOV byte [0xB8001], 0x07
	jmp $

