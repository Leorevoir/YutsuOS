bits    32
global  strcmp
section .text

	; i32 strcmp(const char *s1, const char *s2)

strcmp:
	push ebp
	mov  ebp, esp
	push esi
	push edi

	;.  const char *esi = s1
	;.  const char *edi = s2
	mov esi, [ebp+8]
	mov edi, [ebp+12]

.align_loop:
	;.   while ((u32)esi & 3) {
	;    .   u8 a = *esi
	;    .   u8 b = *edi
	;    .
	;    .   if (a != b) {
	;    .       return (i32)a - (i32)b
	;    .   }
	;    .   if (a == '\0') {
	;    .       return 0
	;    .   }
	;    .
	;    .   ++esi
	;    .   ++edi
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
	;.  for (;; ) {
	;   .  u32 wa = *(u32*)esi
	;   .  u32 wb = *(u32*)edi
	;   .
	;   .  if (wa != wb) {
	;   .      break
	;   .  }
	;   .
	;   .  u32 tmp = (wa - 0x01010101) & ~wa & 0x80808080
	;   .  if (tmp) {
	;   .      return 0
	;   .  }
	;   .
	;   .  esi += 4; edi += 4
	;.  }
	mov eax, [esi]
	mov edx, [edi]
	cmp eax, edx
	jne .word_diff

	mov ecx, eax
	sub ecx, 0x01010101
	not eax
	and eax, ecx
	and eax, 0x80808080
	jnz .equal

	add esi, 4
	add edi, 4
	jmp .word_loop

.word_diff:
.byte_loop:
	;.   while (1) {
	;    .   u8 a = *esi
	;    .   u8 b = *edi
	;    .
	;    .   if (a != b) {
	;    .       return (i32)a - (i32)b
	;    .   }
	;    .
	;    .   if (a == '\0') {
	;    .       return 0
	;    .   }
	;    .   ++esi
	;    .   ++edi
	;.   }
	mov  al, [esi]
	mov  bl, [edi]
	cmp  al, bl
	jne  .byte_diff
	test al, al
	je   .equal
	inc  esi
	inc  edi
	jmp  .byte_loop

.byte_diff:
	;.    return (i32)(u8)a - (i32)(u8)b
	movzx eax, al
	movzx ebx, bl
	sub   eax, ebx
	jmp   .done

.equal:
	xor eax, eax

.done:
	pop edi
	pop esi
	mov esp, ebp
	pop ebp
	ret
