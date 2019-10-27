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

/* here for two reasons, one, this code is GPL (I just haven't bothered to 
 * include the standard warnings) and two, it keeps insmod from complaining */
MODULE_LICENSE("GPL");

/* variables to be filled in at load time by insmod */
static int the_num;
static char *phrase;

/* these macros setup the mechanism for getting parameters from insmod */
MODULE_PARM(the_num, "i");
MODULE_PARM_DESC(the_num, "An important number");
MODULE_PARM(phrase, "s");
MODULE_PARM_DESC(phrase, "A phrase describing the important number");


/* init_module is called when the module is loaded */
int init_module(void) 
{
	printk("<1>module registered: '%i' and '%s' passed in.\n", the_num, phrase);
	return 0;
}


/* cleanup_module is called when the module is unloaded */
void cleanup_module(void)
{
	printk("<1>module with important #%i unregistered\n", the_num);
}

