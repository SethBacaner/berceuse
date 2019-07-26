[org 0x7c00]
KERNEL_OFFSET equ 0x1000

  mov [BOOT_DRIVE], dl	; boot drive is stored by BIOS in dl

  mov bp, 0x9000	; set the stack
  mov sp, bp

  mov bx, MSG_REAL_MODE
  call print_rm

  call load_kernel

  call pm_switch	; will not return to here

  jmp $

%include "gdt.asm"
%include "rm_print.asm"
%include "pm_print.asm"
%include "protected_mode_switch.asm"
%include "disk_load.asm"

[bits 16]

load_kernel:
  mov bx, MSG_LOAD_KERNEL	; still in 16-bit mode, print
  call print_rm			; that we are loading the kernel

  mov bx, KERNEL_OFFSET		; load the first 15 sectors, excluding
  mov dh, 15			; the boot sector from the boot disk
  mov dl, [BOOT_DRIVE]		; to KERNEL_OFFSET
  call disk_load

  ret

[bits 32]
; land here in protected mode
BEGIN_PM:
  mov ebx, MSG_PROT_MODE
  call print_pm

  call KERNEL_OFFSET

  jmp $

; global
BOOT_DRIVE db 0
MSG_REAL_MODE db "Starting in 16-bit Real Mode", 0
MSG_PROT_MODE db "Welcome to 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory.", 0

; bootsector padding
times 510-($-$$) db 0
dw 0xaa55
