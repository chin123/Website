#define __KERNEL__
#define MODULE
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/ptrace.h>
#include <linux/timer.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/highmem.h>
#include <linux/sched.h>

#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/atomic.h>
#include <asm/debugreg.h>
#include <asm/desc.h>
#include <asm/i387.h>

#include <asm/smp.h>
#include <asm/pgalloc.h>
#include <asm/fixmap.h>

#include <linux/irq.h>


asmlinkage void debug(void);

struct desc_struct *idt_table;
struct desc_struct old_debug_idt_entry;

//this was yanked from the kernel
#define _set_gate(gate_addr,type,dpl,addr) \
do { \
  int __d0, __d1; \
  __asm__ __volatile__ ("movw %%dx,%%ax\n\t" \
	"movw %4,%%dx\n\t" \
	"movl %%eax,%0\n\t" \
	"movl %%edx,%1" \
	:"=m" (*((long *) (gate_addr))), \
	 "=m" (*(1+(long *) (gate_addr))), "=&a" (__d0), "=&d" (__d1) \
	:"i" ((short) (0x8000+(dpl<<13)+(type<<8))), \
	 "3" ((char *) (addr)),"2" (__KERNEL_CS << 16)); \
} while (0)

void set_trap_gate(unsigned int n, void *addr)
{
    _set_gate(idt_table+n,15,0,addr);
}

void *idtAddress(void) {
    unsigned int ptr[2];
    __asm__ __volatile__("sidt (%0)": :"p" (((char *) ptr)+2));
    return (void *) ptr[1];
}

void trap_override(void)
{
    idt_table = (struct desc_struct *)idtAddress();
    old_debug_idt_entry = idt_table[1];
    set_trap_gate(1,&debug);
}

void trap_restore(void)
{
    idt_table[1] = old_debug_idt_entry;
}

//this is the new handler for exception number 1
asmlinkage void do_debug(void)
{
    printk("look how cool i am\n");
}

int init_module(void)
{
    trap_override();
    return 0;
}

void cleanup_module(void) 
{
    trap_restore();
}
