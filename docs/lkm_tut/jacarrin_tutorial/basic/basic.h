#ifndef __TEMP_H
#define __TEMP_H

#include <linux/ioctl.h>

#ifndef TEMP_MAJOR
  #define TEMP_MAJOR 0xfd  /* set to 0 to be dynamic */
#endif

//#define DEBUG

#define TEMP_NUMBER 16
#define TEMP_PROC_ENTRY "basic_device"
#define TEMP_DIR_NAME "basic"
#define IRQ_LINE 42

extern struct file_operations basic_fops;

//define all ioctl calls here
#define TEMP_IOC_MAGIC 'k'
#define TEMP_IOCHARDRESET _IO(TEMP_IOC_MAGIC, 0)

#endif /* __TEMP_H */
