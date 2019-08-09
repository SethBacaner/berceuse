/*
 * lib.h
 *
 * Functions and macros for kernel-wide use.
 */

#ifndef BERCEUSE_LIB_H_
#define BERCEUSE_LIB_H_

#include <arch_i386/types.h>

#define KASSERT(expr) \
        ((expr) ? (void)0 : assert_failed(#expr, __FILE__, __LINE__, __func__))

void panic();

void assert_failed(const char *expr,
                   const char *file,
                   int line,
                   const char *func);

void* kmalloc(u32 size);

#endif /* BERCEUSE_LIB_H_ */
