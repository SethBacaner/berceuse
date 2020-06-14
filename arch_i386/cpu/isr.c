#include <arch_i386/isr.h>

#include <arch_i386/idt.h>
#include <arch_i386/timer.h>
#include <keyboard.h>
#include <lib.h>
#include <port.h>

/*
 * Puts three nops in the pipeline so that a previous I/O operation can finish
 * if there is bus contention.
 */
static void do_nops();

void isr_bootstrap()
{
  set_idt_gate(0, (u32)isr0);
  set_idt_gate(1, (u32)isr1);
  set_idt_gate(2, (u32)isr2);
  set_idt_gate(3, (u32)isr3);
  set_idt_gate(4, (u32)isr4);
  set_idt_gate(5, (u32)isr5);
  set_idt_gate(6, (u32)isr6);
  set_idt_gate(7, (u32)isr7);
  set_idt_gate(8, (u32)isr8);
  set_idt_gate(9, (u32)isr9);
  set_idt_gate(10, (u32)isr10);
  set_idt_gate(11, (u32)isr11);
  set_idt_gate(12, (u32)isr12);
  set_idt_gate(13, (u32)isr13);
  set_idt_gate(14, (u32)isr14);
  set_idt_gate(15, (u32)isr15);
  set_idt_gate(16, (u32)isr16);
  set_idt_gate(17, (u32)isr17);
  set_idt_gate(18, (u32)isr18);
  set_idt_gate(19, (u32)isr19);
  set_idt_gate(20, (u32)isr20);
  set_idt_gate(21, (u32)isr21);
  set_idt_gate(22, (u32)isr22);
  set_idt_gate(23, (u32)isr23);
  set_idt_gate(24, (u32)isr24);
  set_idt_gate(25, (u32)isr25);
  set_idt_gate(26, (u32)isr26);
  set_idt_gate(27, (u32)isr27);
  set_idt_gate(28, (u32)isr28);
  set_idt_gate(29, (u32)isr29);
  set_idt_gate(30, (u32)isr30);
  set_idt_gate(31, (u32)isr31);

  pic_remap();

  set_idt_gate(32, (u32)irq0);
  set_idt_gate(33, (u32)irq1);
  set_idt_gate(34, (u32)irq2);
  set_idt_gate(35, (u32)irq3);
  set_idt_gate(36, (u32)irq4);
  set_idt_gate(37, (u32)irq5);
  set_idt_gate(38, (u32)irq6);
  set_idt_gate(39, (u32)irq7);
  set_idt_gate(40, (u32)irq8);
  set_idt_gate(41, (u32)irq9);
  set_idt_gate(42, (u32)irq10);
  set_idt_gate(43, (u32)irq11);
  set_idt_gate(44, (u32)irq12);
  set_idt_gate(45, (u32)irq13);
  set_idt_gate(46, (u32)irq14);
  set_idt_gate(47, (u32)irq15);

  load_idt();
}

void isr_handler(interrupt_frame_t iframe)
{
  kprint("interrupt!\n");
  int int_num = iframe.interrupt_number;
  /* kprint this number. */

  kprint("hello from isr_handler\n");
}

void irq_handler(interrupt_frame_t iframe)
{
  KASSERT(iframe.interrupt_number > 31 && iframe.interrupt_number < 48);

  pic_send_eoi(iframe.interrupt_number);

  switch (iframe.interrupt_number)
  {
    case 32:
      /* IRQ 0 */
      //kprint("handling interrupt 32!\n");
      timer_tick_interrupt(iframe);
      break;
    case 33:
      /* IRQ 1 */
      keyboard_interrupt();
      break;
    default:
      panic();
  }
}

void pic_remap()
{
  u8 pic_master_mask = port_byte_in(PIC_MASTER_DATA);
  u8 pic_slave_mask = port_byte_in(PIC_SLAVE_DATA);

  port_byte_out(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4);
  do_nops();
  port_byte_out(PIC_SLAVE_CMD, ICW1_INIT | ICW1_ICW4);
  do_nops();
  port_byte_out(PIC_MASTER_DATA, 32);
  do_nops();
  port_byte_out(PIC_SLAVE_DATA, 40);
  do_nops();
  port_byte_out(PIC_MASTER_DATA, 0x04);
  do_nops();
  port_byte_out(PIC_SLAVE_DATA, 0x02);
  do_nops();
  port_byte_out(0x21, ICW4_8086);
  do_nops();
  port_byte_out(0xA1, ICW4_8086);
  do_nops();

  port_byte_out(PIC_MASTER_DATA, pic_master_mask);
  port_byte_out(PIC_SLAVE_DATA, pic_slave_mask);
}

void pic_send_eoi(u8 irq)
{
  if (irq >= 8) {
    port_byte_out(PIC_SLAVE_CMD, PIC_EOI);
    do_nops();
  }

  port_byte_out(PIC_MASTER_CMD, PIC_EOI);
}

void do_nops()
{
  __asm__ __volatile__("nop\n\t"
                       "nop\n\t"
                       "nop");
}
