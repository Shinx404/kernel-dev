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
    mov ax, 0x0003
    int 0x10
    mov ah, 0x0e
    mov al, 'B'
    int 0x10
    lgdt [gdtr]
    mov ah, 0x0e
    mov al, 'G'
    int 0x10
    mov sp, 0x7C00
    xor ax, ax
    mov ds, ax
    o32 mov eax, cr0
    o32 or eax, 1
    o32 mov cr0, eax
    jmp 0x08:protected_mode

times 510 - ($ - $$) db 0
dw 0xAA55

BITS 32
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x90000
    mov fs, ax
    mov gs, ax
    mov byte [0xB8000], 'P'
    mov byte [0xB8001], 0x07
    cli
    hlt
