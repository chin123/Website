#inlcude <io.h>

enum { OUTPUT_BUFF = 0x60,
       INPUT_BUFF= 0x60,
       CONTROL_REG = 0x64,
       STATUS_REG = 0x64 };

void keyb_reset( void )
{
    int status;
    
    outb( 0xff, OUTPUT_BUFF ); /*reset keyboard   */ 
    do {
        status = inb( STATUS_REG );
    } while (status & 0x02);

    outb( 0xAA, CONTROL_REG ); /*selftest   */
    inb( INPUT_BUFF );
    outb( 0xAB, CONTROL_REG ); /*interface selftest   */
    inb( INPUT_BUFF );

    outb( 0xAE, CONTROL_REG ); /*enable keyboard   */

    outb( 0xff, OUTPUT_BUFF ); /*reset keyboard   */

    inb( INPUT_BUFF );
    inb( INPUT_BUFF );

    outb( 0xAD, CONTROL_REG ); /*disable keyboard   */


    outb( 0x60, CONTROL_REG );
    outb( 0x01 | 0x04 | 0x20 | 0x40, OUTPUT_BUFF );

    outb( 0xAE, CONTROL_REG ); /*enable keyboard   */
}
