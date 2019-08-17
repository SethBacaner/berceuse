#include <arch_i386/isr.h>

#include <arch_i386/idt.h>
#include <lib.h>
#include <port.h>

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

  u8 pic_master_mask = port_byte_in(PIC_MASTER_DATA);
  u8 pic_slave_mask = port_byte_in(PIC_SLAVE_DATA);

  /* Remaps the PIC (Intel 8259). */

  /* This 0x11 is ICW1_INIT | ICW1_ICW4 */
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

  load_idt();
}

void isr_handler(interrupt_frame_t iframe)
{
  kprint("interrupt!");
  int int_num = iframe.interrupt_number;
  /* kprint this number. */

  kprint("hello from isr_handler");
}

void do_nops()
{
  __asm__ __volatile__("nop\n\t"
                       "nop\n\t"
                       "nop");
}
