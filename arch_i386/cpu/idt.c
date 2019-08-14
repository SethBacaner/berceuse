#include <arch_i386/idt.h>

#include <lib.h>

void set_idt_gate(int n, u32 handler)
{
  idt[n].low_offset = LOW_16(handler);
  idt[n].high_offset = HIGH_16(handler);
  idt[n].segment_selector = KERNEL_CS;
  idt[n].always_zero = 0;
  /*
   * 32-bit interrupt gate.
   */
  idt[n].flags = 0x8E;
}

void load_idt()
{
  idt_register.base = (u32)&idt;
  idt_register.limit = IDT_ENTRIES * sizeof(idt_entry_t) - 1;
  __asm__ __volatile__("lidt (%0)" : : "r" (&idt_register));
}
