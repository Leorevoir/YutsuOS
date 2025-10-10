#ifndef YUTSUOS_CORE_KERNEL_H
#define YUTSUOS_CORE_KERNEL_H

/**
 * @brief initialize the kernel
 */
void __yutsuos_core_kernel_init(void);

/**
 * shutdown | reboot
 */

/**
 * @brief shutdown the system
 */
void __yutsuos_core_kernel_shutdown(void);

/**
 * @brief reboot the system
 */
void __yutsuos_core_kernel_reboot(void);

#endif /* YUTSUOS_CORE_KERNEL_H */
