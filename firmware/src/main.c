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

 /** 
 * \defgroup mainModule
 * \ingroup applicationModule
 *  @{
*/

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "application.h"

static bool bootloader_testRunApplication(void);
static void bootloader_runApplication(void);


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
   // TC0_CompareStart();
    
    // Tests if the application shall run or the bootloader shall continue
    if(bootloader_testRunApplication()) bootloader_runApplication();
    
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

/**
 * This function verifies if the Application requested to start the Bootloader activities.
 * 
 * @return 
 * - true: in case the application shall start 
 */
bool bootloader_testRunApplication(void){
    
    // Set the reserved bootloader RAM segment
    _BOOTLOADER_SHARED_t* pBoot = (_BOOTLOADER_SHARED_t*) _BOOTLOADER_SHARED_RAM;
    uint32_t msp            = *(uint32_t *)(_BOOTLOADER_APPLICATION_BOOT);
    
    bool result = true;
    
    if((pBoot->activation_code0 == _BOOT_ACTIVATION_CODE_START0) && 
       (pBoot->activation_code1 == _BOOT_ACTIVATION_CODE_START1) && 
       (pBoot->activation_code2 == _BOOT_ACTIVATION_CODE_START2) &&      
       (pBoot->activation_code3 == _BOOT_ACTIVATION_CODE_START3) ){ 
       
        result =  false;      
    }else if (msp == 0xffffffff) result = false;
    
    // In case the application should start, the bootloader 
    // upgrade the shared area with the necessary data to be passed to the application
    pBoot->activation_code0 = _BOOT_ACTIVATION_CODE_PRESENCE0;
    pBoot->activation_code1 = _BOOT_ACTIVATION_CODE_PRESENCE1;
    pBoot->activation_code2 = _BOOT_ACTIVATION_CODE_PRESENCE2;
    pBoot->activation_code3 = _BOOT_ACTIVATION_CODE_PRESENCE3;   
    
    pBoot->boot_maj = _BOOTLOADER_REV_MAJ;
    pBoot->boot_min = _BOOTLOADER_REV_MIN;
    pBoot->boot_sub = _BOOTLOADER_REV_SUB;
    
    return result;
    
}


/**
 * This function runs the target application
 */
void bootloader_runApplication(void)
{
    // Set the addresses of the stack pointer and the reset vector of the application
    uint32_t msp            = *(uint32_t *)(_BOOTLOADER_APPLICATION_BOOT);
    uint32_t reset_vector   = *(uint32_t *)(_BOOTLOADER_APPLICATION_BOOT + 4);

  
    // Assignes the Application stack pointer
    __set_MSP(msp);
    
    // Jumps to the main application
    asm("bx %0"::"r" (reset_vector));
}

/*******************************************************************************
 End of File
*/
// @}

