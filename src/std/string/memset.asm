bits    32
global  memset
section .text

	; void *memset(void *ptr, const int value, const u32 num)

memset:

	push ebp
	mov  ebp, esp
	push edi
	push ebx

	;.  u8 *edi = (u8 *)ptr
	;.  u8 *ebx = dest
	;.  u32 ecx = num
	mov edi, [ebp + 8]
	mov ebx, edi
	mov ecx, [ebp + 16]

	;.   if (ecx == 0) return orig
	test ecx, ecx
	jz   .done

	;.    u8 b = (u8)value
	;.    u32 pattern = (u32)b
	;     .   | ((u32)b << 8)
	;     .   | ((u32)b << 16)
	;     .   | ((u32)b << 24)
	movzx eax, byte [ ebp + 12 ]
	mov   edx, eax
	shl   edx, 8
	or    eax, edx
	mov   edx, eax
	shl   edx, 16
	or    eax, edx

	cld

	;.  u32 dwords = count >> 2
	;.  for (u32 i = 0; i < dwords; ++i) {
	;   .    dest += 4
	;.  }
	mov edx, ecx
	shr ecx, 2
	jz  .tail_bytes
	rep stosd

.tail_bytes:
	;.  u32 tail = count & 3
	;.  for (u32 i = 0; i < tail; ++i) {
	;   .   *dest++ = b
	;.  }
	mov ecx, edx
	and ecx, 3
	jz  .done
	rep stosb

.done:
	mov eax, ebx
	pop ebx
	pop edi
	mov esp, ebp
	pop ebp
	ret
