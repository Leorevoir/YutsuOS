bits 32

section .text
%macro  __registers_reset 0
xor     eax, eax
xor     ebx, ebx
xor     ecx, ecx
xor     edx, edx
xor     esi, esi
xor     edi, edi
xor     ebp, ebp
xor     esp, esp
%endmacro

global __yutsuos_core_kernel_qemu_reboot

__yutsuos_core_kernel_qemu_reboot:
	__registers_reset
	mov eax, 0x2000
	mov edx, 0x604
	out dx, eax
	hlt
	ret

global __yutsuos_core_kernel_qemu_shutdown

__yutsuos_core_kernel_qemu_shutdown:
	__registers_reset
	mov eax, 0x2000
	mov edx, 0x604
	out dx, eax
	hlt
	ret
