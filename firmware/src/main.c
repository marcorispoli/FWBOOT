/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "application.h"

bool bootloader_testRunApplication(void);
void bootloader_runApplication(void);


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    TC0_CompareStart();
    
    if(bootloader_testRunApplication()) bootloader_runApplication();
    
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

bool bootloader_testRunApplication(void){
    
    // Set the reserved bootloader RAM segment
    uint32_t *sram = (uint32_t *)0x20000000;    
    for(int i=0; i<4; i++) if(sram[i] != 0x5048434D){
        for(int i=0; i<4; i++) sram[i] = 0;
        return true;
    }
    
    // Reset the shared RAM
    for(int i=0; i<4; i++) sram[i] = 0;    
    return false;
    
}

void bootloader_runApplication(void)
{
    // Set the addresses of the stack pointer and the reset vector of the application
    uint32_t msp            = *(uint32_t *)(_APPLICATION_BOOT);
    uint32_t reset_vector   = *(uint32_t *)(_APPLICATION_BOOT + 4);

    
    // If the application stack pointer is not initialized it means that 
    // no valid application is present
    if (msp == 0xffffffff) return;

    // Assignes the Application stack pointer
    __set_MSP(msp);
    
    // Jumps to the main application
    asm("bx %0"::"r" (reset_vector));
}

/*******************************************************************************
 End of File
*/

