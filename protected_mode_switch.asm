[bits 16]

pm_switch:
  cli				; turn off interrupts
  lgdt [gdt_descriptor]		; load gdt

  mov eax, cr0			; set control register 0 bit, 0
  or eax, 0x1			; to 1 to switch to protected mode
  mov cr0, eax
  jmp CODE_SEG:pm_init


[bits 32]

pm_init:
  mov ax, DATA_SEG		; set segment registers to the ones
  mov ds, ax,			; defined in the gdt data segment
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov ebp, 0x90000		; update stack position
  mov esp, ebp

  call BEGIN_PM
