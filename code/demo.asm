ORG 0x7C00
BITS 16

start:
	JMP main

puts:
	PUSH si
	PUSH ax

.loop:
	LODSB
	OR al, al
	JZ .done
	MOV ah, 0x0e
	MOV bh, 0
	INT 0x10
	JMP .loop
.done:
	POP ax
	POP si
	RET


main:
	MOV ax, 0
	MOV ds, ax
	MOV es, ax

	MOV ss, ax
	MOV sp, 0x7C00

	MOV si, msg_hello
	CALL puts

	HLT
	

.halt:
	JMP .halt


msg_hello: DB 'Hello World', 0

TIMES 510-($-$$) DB 0
DW 0AA55h
