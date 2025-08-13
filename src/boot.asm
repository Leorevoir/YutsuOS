[org 0x7c00]; offset boot sector address

start:
	mov  si, msg
	call print_string
	jmp  $

print_string:
.next_char:
	lodsb
	cmp al, 0
	je  .done
	mov ah, 0x0e
	int 0x10
	jmp .next_char

.done:
	ret

msg   db 'YutsuOS', 0
times 510-($-$$) db 0
dw    0xaa55
