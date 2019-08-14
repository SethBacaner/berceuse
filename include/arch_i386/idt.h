/*
 * idt.h
 *
 * Interrupt descriptor table.
 */

#ifndef BERCEUSE_ARCH_I386_IDT_H_
#define BERCEUSE_ARCH_I386_IDT_H_

#include <arch_i386/types.h>

/* Segment. */
#define KERNEL_CS 0x08

/*
 * 8-byte interrupt descriptor.
 */
typedef struct {
  u16 low_offset;
  u16 segment_selector;
  u8 always_zero;
  u8 flags;
  u16 high_offset;
} __attribute__((packed)) idt_entry_t;


typedef struct {
  u16 limit;  /* Length of the IDT in bytes. */
  u32 base;   /* Base physical address of the IDT. */
} __attribute__((packed)) idt_register_t;

/*
 * Interrupt descriptors live conescutively in this array.
 */
#define IDT_ENTRIES 256
idt_entry_t idt[IDT_ENTRIES];
/*
 *
 */
idt_register_t idt_register;

void set_idt_gate(int i, u32 handler);
void load_idt();

#endif /* BERCEUSE_ARCH_I386_IDT_H_ */
