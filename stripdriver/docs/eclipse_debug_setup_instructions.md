## Setting up the debug environment on Eclipse for the STM32

## Prerequisites 
1. [Eclipse IDE for C/C++ Developers](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/mars2) 
2. [Segger Plugin for Eclipse](https://www.segger.com/IDE_Integration_Eclipse.html)

## Instructions 
1. **File** -> C/C++ -> Existing Code as Makefile Project 
2. Browse for stm32-chibios-template, name Project the same -> **Finish**
3. Ctrl+B, should start make all
4. **Run** -> Debug Configurations  
5. Highlight **GDB SEGGER J-Link Debugging**, and press the 'New' button 
6. Under the **Main Tab**, for C++ Application, select /build_vXX/project.elf
7. Under the **Debugger Tab**, for **Device Name** specify MCU from this [list](https://www.segger.com/jlink_supported_devices.html)
8. Under the **Startup Tab**, for monitor flash device, use the **Device Name** for your MCU 
9. Press **Debug** and the execution should pause at the first breakpoint 
