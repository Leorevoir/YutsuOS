bits 32

ACPI_SHUTDOWN_PORT1 equ 0xB004
ACPI_SHUTDOWN_PORT2 equ 0x604
ACPI_SHUTDOWN_PORT3 equ 0x4004

ACPI_SHUTDOWN_SIGNAL1 equ 0x2000
ACPI_SHUTDOWN_SIGNAL2 equ 0x3400

KEYBOARD_CTRL_PORT equ 0x64
KEYBOARD_DATA_PORT equ 0x60

RESET_CPU equ 0xFE
FORCE_INTERRUPT equ 0x03

section .text

	;---------------------------------------------
	;      void __yutsuos_core_kernel_reboot(void)
	;---------------------------------------------
	global __yutsuos_core_kernel_reboot

__yutsuos_core_kernel_reboot:
	mov al, RESET_CPU
	out KEYBOARD_CTRL_PORT, al

	lidt [.invalid_idt]
	int  FORCE_INTERRUPT

	in  al, 0x92
	or  al, 0x01
	out 0x92, al

	hlt
	ret

.invalid_idt:
	dw 0
	dd 0

	;---------------------------------------------
	;      void __yutsuos_core_kernel_shutdown(void)
	;---------------------------------------------
	global __yutsuos_core_kernel_shutdown

	%macro __shutdown 1
	mov    ax, %1
	out    dx, ax
	%endmacro

__yutsuos_core_kernel_shutdown:
	mov dx, ACPI_SHUTDOWN_PORT1
	__shutdown ACPI_SHUTDOWN_SIGNAL1

	mov dx, ACPI_SHUTDOWN_PORT2
	__shutdown ACPI_SHUTDOWN_SIGNAL1

	mov dx, ACPI_SHUTDOWN_PORT3
	__shutdown ACPI_SHUTDOWN_SIGNAL2

	hlt
	ret
