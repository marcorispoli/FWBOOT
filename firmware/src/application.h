/*!
 * \defgroup  applicationModule Application Modules section
 * 
 */


/*!
 * \defgroup  definitions Application Constants
 * 
 * \ingroup applicationModule
 */


/*!
 * \mainpage
 *
 * # BOOTLOADER OVERVIEW
 *
 * The bootloader firmware, when properly linked with a target 
 * application, allows to add the bootloader feature to the final application.
 * 
 * The bootloader firmware resides into the 0 to 0x1FFF code memory range.
 * 
 * The bootloader cannot change itself: 
 * - the bootloader shall be installed  the first time with the hardware programmer.
 * 
 * When the bootloader is present, it allows to upload the Application segment
 * residing in the upper memory code segment, starting from the 0x2000.
 
 * |CODE ADDRESS|SEGMENTS|
 * |:---|:---|
 * |0:1FFF|Bootloader|
 * |0:2000|Target Application|
 * 
 * 
 * Bootloader an target application share a RAM segment used to pass 
 * data from application segment and bootloader segment:
 * - The RAM segment from 2000000 to 2000000F is reserved for this purpose.
 * 
 * |RAM ADDRESS|SHARED DATA|
 * |:---|:---|
 * |2000000|Activation code 0|
 * |2000001|Activation code 1|
 * |2000002|Activation code 2|
 * |2000003|Activation code 3|
 * |2000004|Bootloader Major revision code|
 * |2000005|Bootloader Minor revision code|
 * |2000006|Bootloader Sub revision code|
 * |2000007|Application Major revision code|
 * |2000008|Application Minor revision code|
 * |2000009|Application Sub revision code|
 * |200000A|Spare|
 * |200000B|Spare|
 * |200000C|Spare|
 * |200000D|Spare|
 * |200000E|Spare|
 * |200000F|Spare|
 * 
 * The Target Application Project shall configure the Starting address to 0x2000.
 * 
 * The Target Application Project shall link the bootloader executable file with 
 * the target object: 
 *  
    ```text
    Menu-Production
    - Set Project Configuration
        - Customize ..
             - Conf: [default]
                - Loading
                    - Add the FWBOOT<zzz>_<xx>.<yy>.hex
    Where:
 *  - <zzz>: is the PCB code;
 *  - <xx>: is the major revision;
 *  - <yy>: is the minor revision;
    ``` 
 *  
 * At the Board power on, the bootloader segment starts executing:
 * - the bootloader fills the shared area with the bootloader revision code; 
 * - the bootloader checks the Activation-Code shared registers to
 * verify if the Application should have request a Bootloader session to run:
 *  - in case the Application had not request the bootloader session 
 *    the bootloader starts the target application;
 *  - in case the Application had requested the bootloader session 
 *    the bootloader starts executing the bootloader functions activating the bootloader CAN protocol;
 * 
 *          
 * # Dependencies 
 * 
 * The Application has been developed with the use of the Microchip Harmony 3
 * libraries. The libraries are a set of source files auto generated by the 
 * Harmony 3 configurator tools and contained into the following directories:
 * - src/config;
 * - src/packs;
 * 
 * ***NOTE: those directories shall never be directly modified since 
 * they are auto-rigenerated every time the generator tool is launched.*** 
 *
 * The libraries make use of the CMSIS 5.4.0 for ARM processors
 * and SAME51_DFP 3.6.130
 *  
 * # HARMONY 3 Device configuration details
 * 
 * The application shall configure the Microcontroller peripheral 
 * with the following rules:
 * 
 * ## Pin configuration
 * 
 *  + The module shall configure the pin for the Can BUS channel 0;
 *  + The module shall configure the pin for the vitality LED;
 *  + The module shall configure the pins for the Main application function;
 * 
 * ## Clock configuration
 * 
 *  + The module shall ***DISABLE*** the FDPLL clock generator: this clock is enabled
 *    by the target application when it runs and  may conflict with this setting if it should be activated!
 *  + The module shall set the GCLK4 to 24 MHz and assign it to the CAN0 peripheral;
 * 
 *  ## SYSTEM Peripheral module setup
 * 
 *  + The module shall ***DISABLE*** the Fuse setting generation because it could get in conflict with 
 *    the Application code:
 *    + SYSTEM/Device & Project Configuration/ATSAME51J20A Device Configuration/Fuse settings:
 *       + Generate Fuse Setting: uncheck this field.
 * 
 * ## CAN0 peripheral module
 * 
 * The CAN0 shall be enabled to receive all the Bootloader frames 
 * targeted to all the System devices, in the range 0x101 to 0x13F.
 * 
 * Follows only those settings that shall be activated.
 * What is not reported is disabled or not modified.
 * 
 * + CAN Operational Mode = NORMAL;
 * + Interrupt Mode: Yes;
 * + Bit Timing Calculation
 *  + Nominal Bit Timing
 *      + Automatic Nominal Bit Timing: Yes;
 *      + BIt Rate: 1000
 * 
 * + Use RX FIFO 0: Yes
 *   + RX FIFO 0 Setting
 *      + Number of element: 1
 * 
 * + Use TX FIFO: Yes
 *   + TX FIFO Setting
 *      + Number of element: 1
 *
 * + EnableTX Pause: YES
 * + Standard Filters 
 *  + Number Of STandard Filters: 1
 *  + Standard Filter 1
 *      + Type: Range;
 *      + ID1: 0x101 
 *      + ID2: 0x13F
 *      + Element Configuration: Store in RX FIFO 0
 *  + Standard message No-Match disposion: Reject
 *  + Reject Standard Remote Frames: YES
 *  + Timestamp Enable: YES    
 * 
 * ## 2.1. Setting the Application Start Address to 0 (default setting)
 * 
 * In the Resource Management (MCC)-Project Graph, select the *System* options:
 * 
 * ```text
 *   Device & Project Configuration
 *    - Project Configuration
 *        - Tool ChainSelections
 *            - XC32 Global Options
 *                - Linker
 *                    - Symbols & Macros
 *                        - Application Start Address (Hex) = 0
 *
 *   ```
 *
 * ## 2.2. Setting the Bootloader shared RAM to 16 byte
 *
 * The application and the bootloader shall share a RAM area in order to pass commands and params. The shared RAM area is 16 byte long 
 * and shall be reserved in the linker section as following described:
 *
 * ```text
 * Menu-Production
 * - Set Project Configuration
 *    - Customize ..
 *        - XC32 Global Options
 *            - XC32-ld
 *                - Additional options: -DRAM_ORIGIN=0x20000010,-DRAM_LENGTH=0x3FFF0 
 * 
 *   ```
 * 
 * # Modules
 *
 * The Application implements the following modules:
 * - @ref applicationModule : defines common objects to the application modules;
 *
 * # Compilation
 * 
 * This software is compiled with the MPLAB-X IDE 6.05:
 * - Compiler: XC32 Vs 3.1
 * 
 * 
 * # Licensing
 *
 * The Application has been developed with the Microchip Harmony 3 libraries 
 * with the Microchip License Agreement conditions as described in:
 * - @ref licenseAgreement 
 *
 * # Documentation
 * 
 * This documentation has been produced with Doxygen 
 * 
 * # Bootloader Usage
 * 
 
 * 
 */



#ifndef _APPLICATION_H    /* Guard against multiple inclusion */
#define _APPLICATION_H

// Defines the Application revision code

/** \addtogroup definitions
 *  @{
*/
static const unsigned char _BOOTLOADER_REV_MAJ = 0; //!< Bootloader Major revision number
static const unsigned char _BOOTLOADER_REV_MIN = 1; //!< Bootloader Minor revision number
static const unsigned char _BOOTLOADER_REV_SUB = 1; //!< Bootloader Sub revision number


static const unsigned long _BOOTLOADER_APPLICATION_BOOT =  0x2000; //!< Application code start address
static const unsigned long _BOOTLOADER_SHARED_RAM =  0x20000000; //!< RAM shared start address
        
static const unsigned char _BOOT_ACTIVATION_CODE_PRESENCE0 = 0x11; //!< Code 0 Bootloader presence
static const unsigned char _BOOT_ACTIVATION_CODE_PRESENCE1 = 0x82; //!< Code 1 Bootloader presence
static const unsigned char _BOOT_ACTIVATION_CODE_PRESENCE2 = 0x13; //!< Code 2 Bootloader presence
static const unsigned char _BOOT_ACTIVATION_CODE_PRESENCE3 = 0x84; //!< Code 3 Bootloader presence

static const unsigned char _BOOT_ACTIVATION_CODE_START0 = 0x1; //!< Code 0 Bootloader start
static const unsigned char _BOOT_ACTIVATION_CODE_START1 = 0x2; //!< Code 1 Bootloader start
static const unsigned char _BOOT_ACTIVATION_CODE_START2 = 0x3; //!< Code 2 Bootloader start
static const unsigned char _BOOT_ACTIVATION_CODE_START3 = 0x4; //!< Code 3 Bootloader start

/**
 * This is the structure of the Shared ram area
 */
typedef struct{
    uint8_t activation_code0; //!< Activation code byte 0
    uint8_t activation_code1; //!< Activation code byte 1
    uint8_t activation_code2; //!< Activation code byte 2
    uint8_t activation_code3; //!< Activation code byte 3

    uint8_t boot_maj;   //!< Bootloader Major revision code
    uint8_t boot_min;   //!< Bootloader Minor revision code
    uint8_t boot_sub;   //!< Bootloader Sub revision code
    uint8_t app_maj;    //!< Application Major revision code
    uint8_t app_min;    //!< Application Mino revision code
    uint8_t app_sub;    //!< Application Sub revision code

    uint8_t sp0;
    uint8_t sp1;
    uint8_t sp2;
    uint8_t sp3;
    uint8_t sp4;
    uint8_t sp5;

}_BOOTLOADER_SHARED_t;

/** @}*/
        
#endif 