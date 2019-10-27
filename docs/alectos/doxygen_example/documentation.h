// a file declaration is not needed in a file that only consists of
// documentation

/** 
 * \fn int top(stack s)
 * \brief Take a look at the top
 * 
 * This is another way to do documentation.
 * It is better to put the documentation in the source, because then you can
 * edit them together.
 *
 * \ingroup stack
 * \return The top of the stack
 */



/**
 * \example stack_example.c  
 * This is an example of how to use the stack struct 
 */



/**
 * \mainpage Sample documentation example
 *
 * \section intro Introduction
 *
 * This tutorial is a simple example of most of the features you will be using
 * in doxygen.  There are many more, but these are the most useful. Next see how
 * you can use this yourself. \ref own
 * 
 */

/**
 * \page own Your own documentation
 *
 * You just need to start putting these structured comments in your .h files and
 * things will be good.  
 * 
 * \section own_1 Step 1: making .h files
 * 
 * \subsection own_1_1 Type stuff
 *
 * First, type some stuff
 *
 * \subsection own_1_2 Add documentation
 *
 * Then add documentation.  
 *
 * \subsection own_1_3 Compile.
 *
 * Then compile
 */
