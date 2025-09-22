bits    32
global  strncmp
section .text

	; i32 strncmp(const char *s1, const char *s2, u32 n)

strncmp:
	push ebp
	mov  ebp, esp
	push esi
	push edi

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
	;.   while (((u32)esi & 3) && ecx > 0) {
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
	;    .   --ecx
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
	;.  while (ecx >= 4) {
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
	;   .  esi += 4; edi += 4; ecx -= 4
	;.  }
	cmp ecx, 4
	jb  .byte_loop
	mov eax, [esi]
	mov edx, [edi]
	cmp eax, edx
	jne .word_diff

	mov ebx, eax
	sub ebx, 0x01010101
	not eax
	and eax, ebx
	and eax, 0x80808080
	jnz .equal

	add esi, 4
	add edi, 4
	sub ecx, 4
	jmp .word_loop

.word_diff:
.byte_loop:
	;.   while (ecx > 0) {
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
	;    .   --ecx
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
