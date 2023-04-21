<center><font size ="6"><b>BOOTLOADER for the SAME51 based boards</b></font></center> 

<font size ="6"><b>Table of content</b></font>

- [1. Overview](#1-overview)
- [2. Target Application setting](#2-target-application-setting)
  - [2.1. *Setting the Application Start Address to 0x2000*](#21-setting-the-application-start-address-to-0x2000)
  - [2.2. *Setting the Bootloader shared RAM to 16 byte*](#22-setting-the-bootloader-shared-ram-to-16-byte)
  - [2.3. *Link the bootloader object file in the target object file*](#23-link-the-bootloader-object-file-in-the-target-object-file)
  - [2.4. *Open the CAN channel 0 acceptance filter for the bootloader activities*](#24-open-the-can-channel-0-acceptance-filter-for-the-bootloader-activities)
- [3. Application usage](#3-application-usage)

# 1. Overview
This document describes the Bootloader functions and the target requirements in order to 
include the bootloader in a target application.

# 2. Target Application setting

The target application, in order to include the bootloader features, shall prepare the project with the following steps:

## 2.1. *Setting the Application Start Address to 0x2000*

In the Resource Management (MCC)-Project Graph, select the *System* options:

```text
Device & Project Configuration
 └─ Project Configuration
     └─ Tool ChainSelections
         └─ XC32 Global Options
             └─ Linker
                 └─ Symbols & Macros
                     └─ Application Start Address (Hex) = 0x2000

```

## 2.2. *Setting the Bootloader shared RAM to 16 byte*

The application and the bootloader shall share a RAM area in order to pass commands and params. The shared RAM area is 16 byte long 
and shall be reserved in the linker section as followiing described:

```text
Menu-Production
 └─ Set Project Configuration
     └─ Customize ..
         └─ XC32 Global Options
             └─ XC32-ld
                 └─ Additional options: -DRAM_ORIGIN=0x20000010,-DRAM_LENGTH=0x3FFF0

```
## 2.3. *Link the bootloader object file in the target object file*

The application needs to include into the target application binary, starting at 0x20000, 
the bootloader binary, starting at 0x0000. The M4 core, at the reset, call the address 0x0000 and needs to find there the bootloader.

```text
Menu-Production
 └─ Set Project Configuration
     └─ Customize ..
         └─ Conf: [default]
             └─ Loading
                 └─ Add the FW_BOOT_xx.yy.hex
```
The **FW_BOOT_xx.yy.hex** is the bootloader binary at the revision **xx**.**yy**

## 2.4. *Open the CAN channel 0 acceptance filter for the bootloader activities*

The bootloader operates over the CAN bus (channel 0) with a proper address range.
The application shall open the 0x1xx address where the xx stands for the CAN ID 
of the target device. See the MET CAN protocol specification for details.

# 3. Application usage

The bootloader features are fully handled by the MET CAN protocol library module.
See the CAN protocol for the usage details.
