#ifndef __KERNEL__
#  define __KERNEL__
#endif
#ifndef MODULE
#  define MODULE
#endif

#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>   
#include <linux/slab.h>    //kmalloc
#include <linux/errno.h>    
#include <linux/types.h>    
#include <linux/proc_fs.h>
#include <linux/fcntl.h>  
#include <linux/init.h>
#include <linux/devfs_fs_kernel.h>
#include <linux/poll.h>
#include <linux/wait.h>
#include <asm/semaphore.h>  

#include "basic.h"          /* local definitions */

static devfs_handle_t basic_dev_dir; 
static int basic_devices[TEMP_NUMBER];
static devfs_handle_t basic_handles[TEMP_NUMBER];
static int is_data_available = 0;
DECLARE_WAIT_QUEUE_HEAD(interrupt_wait_queue);
struct semaphore sem;

static void memory_interrupt_handler(int irq, void *dev_id, struct pt_regs *regs) {
    static int num_ints = 0;
    printk("interupt number %d just happened \n", num_ints);
    is_data_available = 1;
    wake_up_interruptible(&interrupt_wait_queue);
    return;
}

unsigned int basic_poll(struct file *filp, poll_table *wait)
{
    printk("BASIC POLL has been called\n");

    //this is here to notify poll that our status may have changed
    poll_wait(filp, &interrupt_wait_queue, wait);

    //if there is data then we can read it immediately
    return is_data_available ? POLLOUT | POLLIN : POLLOUT;
}

int basic_open(struct inode *inode, struct file *filp)
{
    int i;
    MOD_INC_USE_COUNT;
    printk("minor number is %d\n", inode->i_rdev & 0xff);
    //filp->private_data is a void pointer that you are allowed to use
    //place any data associated with this device in there
    //filp is passed around everywhere.  It is the kernel space equivivent of the
    //file descriptor
    i = inode->i_rdev & 0xff;
    filp->private_data = (void *)i;

    //set the file operations table
    //different minors may have different fops
    filp->f_op = &basic_fops;
    return 0;
}

int basic_release(struct inode *inode, struct file *filp)
{
    int i;

    printk("releasing minor is equal to %d\n", inode->i_rdev & 0xff);
    i = *(int *)filp->private_data;

    MOD_DEC_USE_COUNT;
    return 0;
}

ssize_t basic_read(struct file *filp, char *buf, size_t count, loff_t *ptr)
{
    char a = 'a';
    if(count <= 0)
        return -EINVAL;


    if (filp->f_flags & O_NONBLOCK && !is_data_available)
        return -EAGAIN;

    //wait for the interrupt
    if(wait_event_interruptible(interrupt_wait_queue, is_data_available))
        return -ERESTARTSYS;

    //this will be the a device.
    if(copy_to_user(buf, &a, 1))
        return -EFAULT;

    is_data_available = 0;

    return 1;  //return the number of bytes 
}


ssize_t basic_write(struct file *filp, const char *buf, size_t count, loff_t *ptr)
{
    char my_buf; 
    if(count == 0)
        return -EINVAL;

    //serialize the body of the write function 
    down_interruptible(&sem);

    //use this function insted of mem_cpy because it allows your driver to be
    //reentrant. Memcopy could potenially have to go to disk to get swapped out
    //memory. It returns the number of bytes left to copy if an error
    //occurs,   zero on success.
    if(copy_from_user(&my_buf, buf, 1))
    {
        up(&sem);
        return -EFAULT;
    }
    up(&sem);
    return 1; /*act like you wrote something*/
}


int basic_ioctl (struct inode *inode, struct file *filp,
        unsigned int cmd, unsigned long arg)
{
    int ret = 0;
    switch(cmd) {
        case TEMP_IOCHARDRESET:
            while(MOD_IN_USE)
                MOD_DEC_USE_COUNT;
            MOD_INC_USE_COUNT; // this is because this is open
            break;
        default:
            return -ENOTTY;
    }
    return ret;
}

struct file_operations basic_fops = 
{
            owner:      THIS_MODULE,
            read:       basic_read,
            write:      basic_write,
            ioctl:      basic_ioctl,
            open:       basic_open,
            release:    basic_release,
            poll:       basic_poll,
};

char *temp_service_string = "Rot13Dev /dev/basic/0\notherDev /dev/basic/1\n";

int temp_read_procmem(char *buf, char **start, off_t offset, 
        int count, int *eof, void *data)
{
    //always respond the above string when this proc device is read
    //This can be used for dynamic content to convey information about your device
    if(count > strlen(temp_service_string))
    {
        count = strlen(temp_service_string);
    }
    strncpy(buf, temp_service_string, count);
    *eof = 1;
    return count;
}

//__init => reclaim the memory for this function after init if staticly linked
int __init basic_init()
{
    int i;
    char devname[10];

    for(i=0;i<TEMP_NUMBER;i++)
    {
        basic_devices[i] = i;
    }

    create_proc_read_entry(TEMP_PROC_ENTRY, 
            0, //mode
            NULL, //parent dir
            temp_read_procmem,
            NULL);

    //this creates TEMP_NUMBER devices under a folder named basic in /dev/
    basic_dev_dir = devfs_mk_dir(NULL, "basic", NULL);
    if(!basic_dev_dir)
    {
        return -EBUSY;
    }
    for( i = 0 ; i < TEMP_NUMBER ; i++)
    {
        snprintf(devname, 9, "%i", i);
        devname[9] = '\0';
        basic_handles[i] = devfs_register(basic_dev_dir, 
                devname,
                DEVFS_FL_AUTO_DEVNUM, 
                0, 0,  //major and minor are not needed
                S_IFCHR | S_IRUGO, 
                &basic_fops, basic_devices + i);
    }

    request_irq(IRQ_LINE,  //irq number
            &memory_interrupt_handler,  //handler
            SA_INTERRUPT,   //this means it is a fast int handler
            //fast means that interrupts aren't shut off
            "basic_int",    //name that shows up in /proc/interrupts
            NULL);          //private dev_id to be passed to int handler

    sema_init(&sem, 1);  //only one can hold the semaphore at a time
    return 0;
}

//__exit => this function compiles out when statically linked inthe kernel
void __exit basic_cleanup()
{
    int i;
    remove_proc_entry(TEMP_PROC_ENTRY, NULL);

    for(i=0;i<TEMP_NUMBER;i++)
    {
        devfs_unregister(basic_handles[i]);
    }

    devfs_unregister(basic_dev_dir);
    free_irq(IRQ_LINE, NULL);
}

int init_module()
{
    return basic_init();
}

void cleanup_module()
{
    basic_cleanup();
}

