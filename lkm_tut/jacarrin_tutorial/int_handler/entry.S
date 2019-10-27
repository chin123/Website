#include <linux/config.h>
#include <linux/sys.h>
#include <linux/linkage.h>
#include <asm/segment.h>
#include <asm/smp.h>

ENTRY(debug)
	call SYMBOL_NAME(do_debug)
	iret
