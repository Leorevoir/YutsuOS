print_hex:
	pusha
	mov cx, 0

.start:
	cmp cx, 4
	je  .end

	mov ax, dx
	and ax, 0x000f
	add al, 0x30
	cmp al, 0x39
	jle .print_digit
	add al, 7

.print_digit:
	mov bx, 0x0000 + 5
	sub bx, cx
	mov [bx], al
	ror dx, 4

	add cx, 1
	jmp .start

.end:
	mov  bx, 0x0000
	call print

	popa
	ret
