bits    32
global  strncmp
section .text

	; i32 strncmp(const char *s1, const char *s2, u32 n)

strncmp:
	push ebp
	mov  ebp, esp
	push esi
	push edi
	push ebx

	;.  const char *esi = s1
	;.  const char *edi = s2
	;.  u32 ecx = n
	mov esi, [ebp+8]
	mov edi, [ebp+12]
	mov ecx, [ebp+16]

	;.   if (n == 0) return 0
	test ecx, ecx
	jz   .equal

.align_loop:
	;.   while (((u32)esi & 3) != 0 && ecx > 0)
	;.   {
	;    .   u8 al = *esi
	;    .   u8 bl = *edi
	;    .   if (al != bl) goto .byte_diff
	;    .   if (al == 0) goto .equal
	;    .   esi++
	;    .   edi++
	;    .   ecx--
	;.   }
	test esi, 3
	jz   .word_loop
	test ecx, ecx
	jz   .equal

	mov  al, [esi]
	mov  bl, [edi]
	cmp  al, bl
	jne  .byte_diff
	test al, al
	je   .equal
	inc  esi
	inc  edi
	dec  ecx
	jmp  .align_loop

.word_loop:
	;.  while (ecx >= 4)
	;.  {
	;   .   u32 eax = *(u32 *)esi
	;   .   u32 edx = *(u32 *)edi
	;   .
	;   .   if (eax != edx) goto .handle_word_diff
	;   .
	;   .   u32 temp = eax
	;   .   temp -= 0x01010101
	;   .   eax = ~eax
	;   .   eax &= temp
	;   .   if (eax & 0x80808080) != 0) goto .equal
	;   .
	;   .   esi += 4
	;   .   edi += 4
	;   .   ecx -= 4
	;.  }
	cmp ecx, 4
	jb  .final_bytes

	mov eax, [esi]
	mov edx, [edi]
	cmp eax, edx
	jne .handle_word_diff

	push edx
	mov  edx, eax
	sub  edx, 0x01010101
	not  eax
	and  eax, edx
	and  eax, 0x80808080
	pop  edx
	jnz  .equal

	add esi, 4
	add edi, 4
	sub ecx, 4
	jmp .word_loop

.handle_word_diff:
	;.   for (u32 i = 0; i < min(4, ecx); i++)
	;.   {
	;    .   u8 al = esi[i]
	;    .   u8 bl = edi[i]
	;    .   if (al != bl) goto .word_diff_found
	;    .   if (al == 0) goto .word_diff_equal
	;.   }
	push ecx

	mov  al, [esi]
	mov  bl, [edi]
	cmp  al, bl
	jne  .word_diff_found
	test al, al
	je   .word_diff_equal
	dec  ecx
	jz   .word_diff_equal

	mov  al, [esi+1]
	mov  bl, [edi+1]
	cmp  al, bl
	jne  .word_diff_found
	test al, al
	je   .word_diff_equal
	dec  ecx
	jz   .word_diff_equal

	mov  al, [esi+2]
	mov  bl, [edi+2]
	cmp  al, bl
	jne  .word_diff_found
	test al, al
	je   .word_diff_equal
	dec  ecx
	jz   .word_diff_equal

	mov al, [esi+3]
	mov bl, [edi+3]

.word_diff_found:
	pop ecx
	jmp .byte_diff

.word_diff_equal:
	pop ecx
	jmp .equal

.final_bytes:
	;.   while (ecx > 0)
	;.   {
	;    .   u8 al = *esi
	;    .   u8 bl = *edi
	;    .   if (al != bl) goto .byte_diff
	;    .   if (al == 0) goto .equal
	;    .   esi++
	;    .   edi++
	;    .   ecx--
	;.   }
	test ecx, ecx
	jz   .equal

	mov  al, [esi]
	mov  bl, [edi]
	cmp  al, bl
	jne  .byte_diff
	test al, al
	je   .equal
	inc  esi
	inc  edi
	dec  ecx
	jmp  .final_bytes

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
