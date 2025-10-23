bits    32
section .text

	;      Common ISR/IRQ stub
	%macro ISR_NOERRCODE 1
	global isr%1

isr%1:
	cli
	push 0; push a dummy error code
	push %1; push the interrupt number
	jmp  isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
global isr%1

isr%1:
	cli
	;    error code is already on the stack
	push %1; push the interrupt number
	jmp  isr_common_stub
%endmacro

%macro IRQ 2
global irq%1

irq%1:
	cli
	push 0; dummy error code
	push %2; interrupt number
	jmp  irq_common_stub
%endmacro

extern isr_handler

isr_common_stub:
	pusha
	mov  ax, ds
	push eax
	mov  ax, 0x10
	mov  ds, ax
	mov  es, ax
	mov  fs, ax
	mov  gs, ax

	push esp; push a pointer to the registers_t struct
	call isr_handler
	add  esp, 4; clean up the pushed pointer

	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8
	sti
	iret

	extern irq_handler

irq_common_stub:
	pusha
	mov  ax, ds
	push eax
	mov  ax, 0x10
	mov  ds, ax
	mov  es, ax
	mov  fs, ax
	mov  gs, ax

	push esp; push a pointer to the registers_t struct
	call irq_handler
	add  esp, 4; clean up the pushed pointer

	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8
	sti
	iret

	; ISR stubs (0-31)
	ISR_NOERRCODE 0
	ISR_NOERRCODE 1
	ISR_NOERRCODE 2
	ISR_NOERRCODE 3
	ISR_NOERRCODE 4
	ISR_NOERRCODE 5
	ISR_NOERRCODE 6
	ISR_NOERRCODE 7
	ISR_ERRCODE   8
	ISR_NOERRCODE 9
	ISR_ERRCODE   10
	ISR_ERRCODE   11
	ISR_ERRCODE   12
	ISR_ERRCODE   13
	ISR_ERRCODE   14
	ISR_NOERRCODE 15
	ISR_NOERRCODE 16
	ISR_ERRCODE   17
	ISR_NOERRCODE 18
	ISR_NOERRCODE 19
	ISR_NOERRCODE 20
	ISR_NOERRCODE 21
	ISR_NOERRCODE 22
	ISR_NOERRCODE 23
	ISR_NOERRCODE 24
	ISR_NOERRCODE 25
	ISR_NOERRCODE 26
	ISR_NOERRCODE 27
	ISR_NOERRCODE 28
	ISR_NOERRCODE 29
	ISR_ERRCODE   30
	ISR_NOERRCODE 31

	;   IRQ stubs (32-47)
	IRQ 0, 32
	IRQ 1, 33
	IRQ 2, 34
	IRQ 3, 35
	IRQ 4, 36
	IRQ 5, 37
	IRQ 6, 38
	IRQ 7, 39
	IRQ 8, 40
	IRQ 9, 41
	IRQ 10, 42
	IRQ 11, 43
	IRQ 12, 44
	IRQ 13, 45
	IRQ 14, 46
	IRQ 15, 47
