<center><font size ="6"><b>BOOTLOADER for SAME51 based boards</b></font></center> 
<br>
<br>
<br>
<br>


<font size ="6"><b>Table of content</b></font>

- [1. Project directory overview](#1-project-directory-overview)
  - [1.1. MPLAB-X Progect directory](#11-mplab-x-progect-directory)
  - [1.2. Project source directory](#12-project-source-directory)
  - [1.3. Project documentation directory](#13-project-documentation-directory)
- [2. Project documentation](#2-project-documentation)
- [3. Project Environ revision](#3-project-environ-revision)

# 1. Project directory overview

## 1.1. MPLAB-X Progect directory

firmware
 └─ FW_BOOT.X

## 1.2. Project source directory

firmware
 └─ src

## 1.3. Project documentation directory

firmware
 └─ doc

# 2. Project documentation

This project has been documented with Doxygen.
The Doxygen project file is: 
 
```text
  firmware
    └─doc
        └─ fwboot_doxygen
```

The Document is compiled in HTML format.

The HTML Document index is:

```text
  firmware
    └─doc
        └─ index.html
```

This document describes the Bootloader functions and the target requirements in order to 
include the bootloader in a target application.

# 3. Project Environ revision

- mcc_version: v5.3.0
- mcc_core_version: v5.5.0
- mplabx_version: v6.05        # if MPLAB X plugin only
- harmony_version: v1.3.0
- compiler: XC32 (v3.01) 

- modules:
    - {name: "csp", version: "v3.9.1"}
    - {name: "dev_packs", version: "v3.9.0"}


