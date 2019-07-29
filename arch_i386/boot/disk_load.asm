; load dh sectors os es:b from drive dl
disk_load:
  push dx

  mov ah, 0x02		; BIOS low level disk
  mov al, dh		; services - read sectors
  mov ch, 0x00		; cylinder 0
  mov dh, 0x00		; head 0
  mov cl, 0x02		; sector 2 (after the boot sector

  int 0x13		; BIOS disk low level disk services

  jc disk_error		; jump if error

  pop dx
  cmp dh, al		; if al (sectors read) != dh (sectors expected)
  jne disk_error	; display error message
  ret

disk_error:
  mov bx, DISK_ERROR_MSG
  call print_rm
  jmp $

DISK_ERROR_MSG db "Disk read error.", 0
