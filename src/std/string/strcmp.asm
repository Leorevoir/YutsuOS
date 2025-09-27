bits    32
global  strcmp
section .text

	; i32 strcmp(const char *s1, const char *s2)

strcmp:
	push ebp
	mov  ebp, esp
	push esi
	push edi
	push ebx

	;   const char *esi = s1
	;   const char *edi = s2
	mov esi, [ebp+8]
	mov edi, [ebp+12]

.align_loop:
	;.   while ((u32)esi & 3) != 0
	;.   {
	;    .   u8 al = *esi
	;    .   u8 bl = *edi
	;    .   if (al != bl) goto .byte_diff
	;    .   if (al == 0) goto .equal
	;    .   esi++
	;    .   edi++
	;.   }
	test esi, 3
	jz   .word_loop

	mov  al, [esi]
	mov  bl, [edi]
	cmp  al, bl
	jne  .byte_diff
	test al, al
	je   .equal
	inc  esi
	inc  edi
	jmp  .align_loop

.word_loop:
	;.  for (;; )
	;.  {
	;   .   u32 eax = *(u32 *)esi
	;   .   u32 edx = *(u32 *)edi
	;   .
	;   .   if (eax != edx) goto .handle_word_diff
	;   .
	;   .   u32 ecx = eax
	;   .   ecx -= 0x01010101
	;   .   eax = ~eax
	;   .   eax &= ecx
	;   .   if (eax & 0x80808080) != 0) goto .equal
	;   .
	;   .   esi += 4
	;   .   edi += 4
	;.  }
	mov eax, [esi]
	mov edx, [edi]
	cmp eax, edx
	jne .handle_word_diff

	mov ecx, eax
	sub ecx, 0x01010101
	not eax
	and eax, ecx
	and eax, 0x80808080
	jnz .equal

	add esi, 4
	add edi, 4
	jmp .word_loop

.handle_word_diff:
	;.   u8 al = esi[0], bl = edi[0]
	;.   if (al != bl) goto .byte_diff
	;.   if (al == 0) goto .equal
	;.
	;.   al = esi[1], bl = edi[1]
	;.   if (al != bl) goto .byte_diff
	;.   if (al == 0) goto .equal
	;.
	;.   al = esi[2], bl = edi[2]
	;.   if (al != bl) goto .byte_diff
	;.   if (al == 0) goto .equal
	;.
	;.   al = esi[3], bl = edi[3]
	;.   goto .byte_diff
	mov  al, [esi]
	mov  bl, [edi]
	cmp  al, bl
	jne  .byte_diff
	test al, al
	je   .equal

	mov  al, [esi+1]
	mov  bl, [edi+1]
	cmp  al, bl
	jne  .byte_diff
	test al, al
	je   .equal

	mov  al, [esi+2]
	mov  bl, [edi+2]
	cmp  al, bl
	jne  .byte_diff
	test al, al
	je   .equal

	mov al, [esi+3]
	mov bl, [edi+3]
	jmp .byte_diff

.byte_diff:
	;.    return (i32)(u8)al - (i32)(u8)bl
	movzx eax, al
	movzx ebx, bl
	sub   eax, ebx
	jmp   .done

.equal:
	xor eax, eax

.done:
	pop ebx
	pop edi
	pop esi
	mov esp, ebp
	pop ebp
	ret
