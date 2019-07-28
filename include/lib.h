/*
 * lib.h
 *
 * Funcions and macros for kernel-wide use.
 */

#ifndef KERNEL_LIB_H_
#define KERNEL_LIB_H_

#define KASSERT(expr) \
        ((expr) ? (void)0 : assert_failed(#expr, __FILE__, __LINE__, __func__))

void panic();

void assert_failed(const char *expr,
                   const char *file,
                   int line,
                   const char *func);

#endif // KERNEL_LIB_H_
