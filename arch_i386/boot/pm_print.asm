[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f		; 0x04?

print_pm:
  pusha
  mov edx, VIDEO_MEMORY		; set edx to be start of video memory

print_pm_loop:
  mov al, [ebx]			; set al to char in ebx
  mov ah, WHITE_ON_BLACK	; set ah to color setting

  cmp al, 0			; al == 0 => end of string
  je print_pm_done		; so jump to done

  mov [edx], ax			; store char and color setting
				; to current cell
  add ebx, 1			; increment to next char in string
  add edx, 2			; move to next cell in video memory

  jmp print_pm_loop		; do another print

print_pm_done:
  popa
  ret
