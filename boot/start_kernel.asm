[bits 32]	
[extern kmain] 	; kmain is an external symbol that will
		; be resolved during linking
call kmain
jmp $
