bits    32
global  __yutsuos_core_idt_load
section .text

__yutsuos_core_idt_load:
	mov  eax, [esp + 4]; get the address of the IDT pointer
	lidt [eax]; load the IDT register
	ret
