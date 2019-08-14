;
; interrupt.asm
;

; Defined in isr.c.
[extern isr_handler]

;KERNEL_DS equ 0x10

isr_common:
  pusha
  mov ax, ds
  push eax
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call isr_handler

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  popa
  add esp, 8
  sti
  iret

; ISR routines are declared global so that
; isr.c can see them when interrupts are bootstrapped
; on kernel startup.
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; Division by zero
isr0:
  cli
  push byte 0
  push byte 0
  jmp isr_common

; Debug exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common

; 2: Non Maskable Interrupt
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common

; Int 3 exception (breakpoint)
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common

; INTO exception (integer overflow)
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common

; Out of Bounds
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common

; Invalid Opcode
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common

; Coprocessor Not Available
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common

;  Double Fault with error code
isr8:
    cli
    push byte 8
    jmp isr_common

; Coprocessor Segment Overrun
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common

; Bad TSS with error code
isr10:
    cli
    push byte 10
    jmp isr_common

; Segment Not Present with error code
isr11:
    cli
    push byte 11
    jmp isr_common

; Stack Fault with error code
isr12:
    cli
    push byte 12
    jmp isr_common

; General Protection Fault with error code
isr13:
    cli
    push byte 13
    jmp isr_common

; Page Fault with error code
isr14:
    cli
    push byte 14
    jmp isr_common

; Reserved
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common

; Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common

; Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common

; Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common

; Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common

; Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common

; Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common

; Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common

; Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common

; Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common

; Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common

; Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common

; Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common

; Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common

; Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common

; Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common

; Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common
