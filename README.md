# HelloSTM32F746 - led blink
## Sample evaluation project for STM32F746

Project generated using MX perspective in STM32CubeIDE, version 1.3.0.

Application is en example of using interrupts and basic timer to blink a LED. Using user button you can switch LED blinking period (1s / 100ms). 
Remark: Classes Led and UserButton are not used, its only an example of GPIO configuration for port GPIOI - pin 1 and pin 11 of STM32F746NG DISCOVERY board.

Project contains MBED tools in MBEDTLS & MiddleWares directory.
Folders ./Core/src and ./Core/inc contain generated boilerplate code and FreeModbus library source code (freeModbus\modbus).

Folder ./Core/src/port contains initial files requred to build FreeModbus port for STM32 microcontroller, taken from 
(directory freeModbus/Demo/BARE/port and also files freeModbus/Demo/BARE/demo.c, freeModbus/Demo/BARE/Makefile).
