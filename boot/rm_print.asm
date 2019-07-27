; print string in 16-bit real mode using bios
; interrupt routine. string address of the string
; is in bx
[bits 16]
print_rm:
  pusha
  mov ah, 0x0e		; write character in TTY mode

print_rm_loop:
  mov al, [bx]

  cmp al, 0
  je print_rm_done

  int 0x10		; bios interrupt vector for video
			; services

  add bx, 1		; move to next character in bx

  jmp print_rm_loop

print_rm_done:
  popa
  ret
