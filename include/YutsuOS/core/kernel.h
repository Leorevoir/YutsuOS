#ifndef YUTSUOS_CORE_KERNEL_H
#define YUTSUOS_CORE_KERNEL_H

/**
 * @brief shutdown the system (QEMU)
 */
void __yutsuos_core_kernel_shutdown(void);

/**
 * @brief reboot the system (QEMU)
 */
void __yutsuos_core_kernel_reboot(void);

#endif /* YUTSUOS_CORE_KERNEL_H */
