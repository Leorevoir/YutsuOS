bits    32
global  strlen
section .text

	; u32 strlen(const char *str)

strlen:
	push ebp
	mov  ebp, esp

	;.  const char *edx = str
	;.  u32 eax = 0
	mov edx, [ebp+8]
	xor eax, eax

.loop:
	;.  while (edx[eax] != 0) ++eax
	cmp byte [edx+eax], 0
	je  .done
	inc eax
	jmp .loop

.done:
	pop ebp
	ret
