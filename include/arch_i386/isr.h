#ifndef BERCEUSE_ARCH_I386_ISR_H_
#define BERCEUSE_ARCH_I386_ISR_H_

#include <arch_i386/types.h>

#define PIC_MASTER_CMD  0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD   0xA0
#define PIC_SLAVE_DATA  0xA1

/* End of Interrupt command. */
#define PIC_EOI 0x20

/* Initialiation Command Words for Intel 8259A PIC */
#define ICW1_ICW4	0x01
#define ICW1_INIT	0x10
#define ICW4_8086	0x01

/* Defined in interrupt.asm */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

typedef struct {
  u32 ds;
  u32 edi;
  u32 esi;
  u32 ebp;
  u32 esp;
  u32 ebx;
  u32 edx;
  u32 ecx;
  u32 eax;
  u32 interrupt_number;
  u32 error_code;
  u32 eip;
  u32 cs;
  u32 eflags;
  u32 useresp;
  u32 ss;
} interrupt_frame_t;

void isr_bootstrap();
void isr_handler(interrupt_frame_t iframe);

/*
 * Remaps the PIC (Intel 8259).
 */
void pic_remap();

/*
 * Tells master and slave (if applicable for the irq number) to turn off the
 * interrupt line so that we can receive more interrupts.
 */
void pic_send_eoi(u8 irq);

#endif /* BERCEUSE_ARCH_I386_ISR_H_ */
