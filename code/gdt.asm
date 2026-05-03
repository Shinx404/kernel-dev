gdt_start:
	DQ 0

gdt_code:
	DW 0xFFFF
	DW 0
	DB 0
	DB 0x9A
	DB 0xCF
	DB 0

gdt_data:
	DW 0xFFFF
	DW 0
	DB 0
	DB 0x92
	DB 0xCF
	DB 0

gdt_end:

gdtr:	
	DW 0
	DD 0

setGdt:
   XOR   EAX, EAX
   MOV   AX, DS
   SHL   EAX, 4
   ADD   EAX, gdt_start
   MOV   [gdtr + 2], eax
   MOV   EAX, gdt_end
   SUB   EAX, gdt_start
   MOV   [gdtr], AX
   LGDT  [gdtr]
   RET
