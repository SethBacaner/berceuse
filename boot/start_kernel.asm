global _start;
[bits 32]	

; kmain is an external symbol that ld will resolve during linking.
_start:
	[extern kmain]
	call kmain
	jmp $
