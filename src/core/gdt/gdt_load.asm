bits    32
global  __yutsuos_core_gdt_load
section .text

KERNEL_DATA_SEGMENT equ 0x10
KERNEL_CODE_SEGMENT equ 0x08

__yutsuos_core_gdt_load:
	mov  eax, [esp+4]
	lgdt [eax]

	mov ax, KERNEL_DATA_SEGMENT
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp KERNEL_CODE_SEGMENT:.flush

.flush:
	ret
