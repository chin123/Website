/* simple_char.c - A simple character device kernel module
 * Copyright (C) 2002  Dave Goodell <dgoodell@uiuc.edu>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */


/*  extremely brief instructions for use:
	   make
		insmod simple_char.o
		cat /proc/devices    (find what major number was registered to simple_char)
		mknod /dev/simple_char0 c <# from /proc/devices> 0
	**At this point, you can play around w/ the device (cat is 
	**about all you can really do to it). When finished:
		rm /dev/simple_char0
		rmmod simple_char

		And that's about it
		--DJG
*/


/* kernel code needs to have this defined */
#define __KERNEL__

/* needed for versioned kernels (i.e. most kernels in current use) */
#ifdef MODVERSIONS
#include <linux/modversions.h>
#endif

/* needed to make a module */
#ifdef MODULE
#include <linux/module.h>
#endif

/* needed to deal w/ being a char device */
#include <linux/fs.h>

/* needed to deal w/ userspace memory */
#include <asm/uaccess.h>

/* to get the string functions */
#include <linux/string.h>


/* here for two reasons, one, this code is GPL (I just haven't bothered to 
 * include the standard warnings) and two, it keeps insmod from complaining */
MODULE_LICENSE("GPL");
/* tells everybody who wrote the module */
MODULE_AUTHOR("Dave Goodell");
/* gives a brief description of what the module does */
MODULE_DESCRIPTION("This module provides a simple example of a character device");


static int major_num = 0;		/* default to 0 (dynamic), allowing override */
MODULE_PARM(major_num, "i");
MODULE_PARM_DESC(major_num, "The major number associated with this driver");

static char default_phrase[128] = "this is the boring default phrase because someone "
                                  "was too lazy to pass a parameter to insmod\n";
static char *phrase;
static unsigned int phrase_length;
MODULE_PARM(phrase, "s");
MODULE_PARM_DESC(phrase, "The phrase that will be sent back by the driver on read()");

/* the name of the device for /proc/devices (nothing special about NAME, the 
	actual name gets set by the register_chrdev() call) */
#define NAME "simple_char"

/* XXX */
#if 0
/* size of the "scratch" buffer */
#define SCRATCH_SIZE 50

/* the "scratch" area of the device */
static char scratch_area[SCRATCH_SIZE] = "bleh, this is the scratch message\n";
#endif


int simple_open(struct inode *inode, struct file *filp)
{
	/* increment the usage count */
	MOD_INC_USE_COUNT;
	
	return 0;
}

int simple_release(struct inode *inode, struct file *filp)
{
	/* decrement the usage count */
	MOD_DEC_USE_COUNT;

	return 0;
}

#define EOF 0
ssize_t simple_read(struct file *filp, char *buff, size_t count, loff_t *offp)
{
	int num_xfered = 0;

	/* return EOF if an offset beyond the buffer size is requested */
	if (*offp >= phrase_length)
	{
		printk(KERN_DEBUG "simple_read(): EOF reached\n");
		return num_xfered;
	}

	/* decide how much to actually send back (being careful not to read beyond the length of our buffer) */
	num_xfered = (*offp + count < phrase_length ? count : phrase_length - *offp);

	/* we can't actually reference user-land memory directly, as it may be swapped out currently...
		as such, we have to use special functions to deal w/ that memory (ie, not memcpy) */
	copy_to_user(buff, phrase + *offp, num_xfered);

	/* update the current position in the file */
	*offp += num_xfered;

	/* send back the number of bytes we transfered to buff */
	printk(KERN_DEBUG "simple_read(): num_xfered=%d\n", num_xfered);
	return num_xfered;
}


/* this structure tells the kernel which operations are supported and how */
static struct file_operations simple_fops = {
	open: simple_open,
	release: simple_release,
	read: simple_read
};



/* init_module is called when the module is loaded */
int init_module(void) 
{
	int result;

	/* set the owner field of simple_fops */
	SET_MODULE_OWNER(&simple_fops);

	printk(KERN_DEBUG "registering simple_char\n");
	result = register_chrdev(major_num, NAME, &simple_fops);

	if (result < 0)		/* report any problems during registration */
	{
		printk(KERN_WARNING "simple_char: unsuccessful request of major #: %d\n", major_num);
		return result;
	}

	/* get and cache the length of the phrase */
	if (phrase == NULL)
		phrase = default_phrase;

	phrase_length = strlen(phrase);

	/* if we're using dynamic allocation, find out which # we were assigned */
	if (major_num == 0) 
		major_num = result;

	return 0;
}


/* cleanup_module is called when the module is unloaded */
void cleanup_module(void)
{
	int result;

	printk(KERN_DEBUG "unregistering simple_char\n");

	/* we have to make sure and clean up after ourselves */
	result = unregister_chrdev(major_num, NAME);
	if (result < 0)
	{
		printk(KERN_WARNING "simple_char: unregister_chrdev(%d, " NAME ") returned '%d'\n", major_num, result);
	}
}

