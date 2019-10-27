/* sample.h
 *
 */

#ifndef __SAMPLE_H
#define __SAMPLE_H

#include "something.h"
#include <stdio.h>

/** \file
 *  \brief This is brief description of this file
 *
 *  This is a slightly longer description of the file.  Also note that the
 *  'backslash'file command is needed or doxygen wont pull any declarations from
 *  the file
 * \version a million
 * \author someone without much to do
 * \author some other guy too
 * \date 1896-2430
 */
//Note version, author, and date can be listed under a struct or a function, or
//any other thing that can be documented


///This describes this #define and what it is used for. 
///In this case it is used to say there is no memory. 
///These are automatically brief descriptions
#define ENOMEM -1

///you may also only have one line of comments
#define EXAMPLE -2

#define EXAMPLE2 -3  ///< This is how you put documentation after the fact

//Note: it is better, however to put the documentation before the item

/** \addtogroup stack */
/** \{ */   


/**
 * \brief This is a stack struct
 *
 * It does stack stuff
 * \author ME
 */

typedef struct
{
        int start;          /**< \brief This is the start of the stack
                             *
                             * and multiline too, with details. */ 
        int end;            ///<There are automatically brief descriptions
        
        /**
         * \brief This is the data of the stack. 
         * This is a second line of brief description
         *
         * If you do it this way, they dont only have to be brief descriptions
         */
        int stack[100];     

        ///ID number
        int id;

        ///It handles these good too. 
        ///This is a pointer to a function that takes 2 ints and a char * 
        ///and returns a void *
        void *(*helper)(int, int, char *);
} stack;




/**
 * \brief This function is used to push stuff
 * 
 * It puts stuff on the end.
 * 
 * \bug this function rules too much
 * \param s This is the stack to push onto
 * \param val This is the value to push
 *
 * \return 
 *      - a non-negative value indicates success
 *      - a negative return value indicates that the push was not successful
 *      - The - creates a bullet list
 */
int push(stack s, int val);
/** \} */



/**
 * \brief This pops
 *
 * It is used to pop stuff
 *
 * \ingroup stack
 * \warning This can give you an error if there is nothing to pop
 * \see stack
 * \see push
 * \param s the stack to get an element from
 *
 * \return
 * 
 */

int pop(stack s);

/**
 * \brief This gets an element
 *
 * It is used to get stuff
 *
 * \deprecated Dont use this anymore, for various reasons
 * \param s stack to get item from
 * \param i This is the index
 * 
 * \return
 * 
 */
int get_elem(stack s, int val);


int top(stack s);





#endif



