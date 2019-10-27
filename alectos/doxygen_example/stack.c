/* stack.c
 */

/** \file 
 */

#include "stack.h"

/* this is a note about the bug that exists here */
int push(stack s, int val)
{
    s.end++;
    s.stack[s.end] = val;
    return 0;
}

/**
 * \todo Impliment this function
 */

int pop(stack s, int val)
{

}

