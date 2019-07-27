/*
 * port.h
 *
 * Low level I/O functions.
 */

#ifndef KERNEL_PORT_H_
#define KERNEL_PORT_H_

unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);

unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);

#endif /* KERNEL_PORT_H_ */
