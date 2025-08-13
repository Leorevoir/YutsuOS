[org 0x7c00]

	jmp $

times 511-($-$$) db 0
dw    0xaa56

