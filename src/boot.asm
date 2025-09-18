bits 32

section .multiboot
    align 4
    dd 0x1BADB002               ; bootloader magic number
    dd 0x00                     ; flags
    dd - (0x1BADB002 + 0x00)    ; checksum

section .text
    global _start
    extern main                 ; kernel.c

_start:
    cli                         ; block interrupts
    mov esp, stack_space        ; set stack pointer
    call main                   ; call int main(void) from kernel.c
    hlt                         ; halt the CPU

section .bss
resb 8192                       ; stack size: ~8kb
stack_space:
