; Global Descriptor Table for switch to 32-bit protected mode
gdt_start:

gdt_null:
  dd 0x0		; declare double word (4 bytes since
  dd 0x0		; we are in 16-bit real mode)

gdt_code:		; code segment descriptor
  dw 0xffff
  dw 0x0
  db 0x0
  db 10011010b		; 0x9a
  db 11001111b		; 0xcf
  db 0x0

gdt_data:		; data segment descriptor
  dw 0xffff
  dw 0x0
  db 0x0
  db 10010010b		; 0x92
  db 11001111b		; 0xcf
  db 0x0

gdt_end:



gdt_descriptor:
  dw gdt_end - gdt_start - 1
  dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
