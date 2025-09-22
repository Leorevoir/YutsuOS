bits    32
global  strlen
section .text

	; u32 strlen(const char *str)

strlen:
	push ebp
	mov  ebp, esp
	push edi

	;.  const char *edi = str
	;.  u32 eax = 0
	mov edi, [ebp+8]
	xor eax, eax

.align_loop:
	;.   while ((u32)edi & 3) != 0
	;.   {
	;    .   if (*edi == 0) return eax
	;    .   ++edi
	;    .   ++eax
	;.   }
	test edi, 3
	jz   .word_loop
	mov  dl, [edi]
	test dl, dl
	je   .done
	inc  edi
	inc  eax
	jmp  .align_loop

.word_loop:
	;.  for (;; )
	;.  {
	;   .   u32 edx = *(u32 *)edi
	;   .
	;   .   if (((edx - 0x01010101) & ~edx & 0x80808080) != 0) break
	;   .   edi += 4
	;   .   eax += 4
	;.  }
	mov edx, [edi]
	mov ecx, edx
	sub ecx, 0x01010101
	not edx
	and edx, ecx
	and edx, 0x80808080
	jnz .byte_scan
	add edi, 4
	add eax, 4
	jmp .word_loop

.byte_scan:
.byte_loop:
	;.   while (*edi != '\0')
	;.   {
	;    .   edi++
	;    .   eax++
	;.   }
	mov  dl, [edi]
	test dl, dl
	je   .done
	inc  edi
	inc  eax
	jmp  .byte_loop

.done:
	pop edi
	mov esp, ebp
	pop ebp
	ret

