/*
 * kmalloc.c
 *
 * Heap dynamic memory allocation.
 */

#include <lib.h>

u32 free_memory_addr = 0x20000;

void* kmalloc(u32 size)
{
  u32 return_addr = free_memory_addr;
  free_memory_addr += size;
  return (void*)return_addr;
}
