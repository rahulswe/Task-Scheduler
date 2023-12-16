# Task-Scheduler

This repository contains a simple implementation of a round robin pre-emptive scheduling policy based task scheduler. The linker script and startup file for this project has be written from scratch for the STM32 NUCLEOF446RE developement board comprising of Cortex-M4 processor.

There are 4 user tasks (Task1, Task2, Task3 and Task4). Each of these task's handler looks like this -

```
void task1_handler() {
	while(1) {
		printf("Task1 Running\n");
	}
}
```

It basically prints a message indicating that particular is currently running. In addition there is an idle task which could get a chance to run when no other task can run i.e. when they are in blocked state due to task_delay function call. In the current implementation, since we don't call this function from any of the user task handlers, the idle task never gets a chance to run.


## Pre-Requisite

### Software
1) GNU Arm Embedded Toolchain (https://developer.arm.com/downloads/-/gnu-rm)
2) Openocd
3) Make

### Hardware
1) STM32 NUCLEOF446RE Board (Cortex-M4)

Note: Any other Cortex-M4 based MCU may be used but would require corresponding changes to be done in the startup and linker file.

## Building the application

```shell
> make ARM_SEMIHOSTING=Enable

mkdir -p Build/obj/./
arm-none-eabi-gcc -I. -I./Inc -I./.git -I./.git/objects -I./.git/objects/95 -I./.git/objects/92 -I./.git/objects/3c -I./.git/objects/3d -I./.git/objects/94 -I./.git/objects/a3 -I./.git/objects/ab -I./.git/objects/eb -I./.git/objects/ee -I./.git/objects/e3 -I./.git/objects/cf -I./.git/objects/ca -I./.git/objects/fb -I./.git/objects/18 -I./.git/objects/pack -I./.git/objects/29 -I./.git/objects/1a -I./.git/objects/4c -I./.git/objects/26 -I./.git/objects/6b -I./.git/objects/07 -I./.git/objects/5c -I./.git/objects/info -I./.git/objects/65 -I./.git/objects/30 -I./.git/objects/39 -I./.git/objects/d3 -I./.git/objects/a9 -I./.git/objects/de -I./.git/objects/a6 -I./.git/objects/c3 -I./.git/objects/c2 -I./.git/objects/e7 -I./.git/objects/cb -I./.git/objects/46 -I./.git/objects/79 -I./.git/objects/1e -I./.git/objects/24 -I./.git/objects/8d -I./.git/objects/76 -I./.git/objects/40 -I./.git/objects/7f -I./.git/info -I./.git/logs -I./.git/logs/refs -I./.git/logs/refs/heads -I./.git/logs/refs/remotes -I./.git/logs/refs/remotes/origin -I./.git/hooks -I./.git/refs -I./.git/refs/heads -I./.git/refs/tags -I./.git/refs/remotes -I./.git/refs/remotes/origin -I./Src -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -std=gnu11 -Wall --save-temps  -c stm32_startup.c -o Build/obj/./stm32_startup.o
mkdir -p Build/obj/./Src/
arm-none-eabi-gcc -I. -I./Inc -I./.git -I./.git/objects -I./.git/objects/95 -I./.git/objects/92 -I./.git/objects/3c -I./.git/objects/3d -I./.git/objects/94 -I./.git/objects/a3 -I./.git/objects/ab -I./.git/objects/eb -I./.git/objects/ee -I./.git/objects/e3 -I./.git/objects/cf -I./.git/objects/ca -I./.git/objects/fb -I./.git/objects/18 -I./.git/objects/pack -I./.git/objects/29 -I./.git/objects/1a -I./.git/objects/4c -I./.git/objects/26 -I./.git/objects/6b -I./.git/objects/07 -I./.git/objects/5c -I./.git/objects/info -I./.git/objects/65 -I./.git/objects/30 -I./.git/objects/39 -I./.git/objects/d3 -I./.git/objects/a9 -I./.git/objects/de -I./.git/objects/a6 -I./.git/objects/c3 -I./.git/objects/c2 -I./.git/objects/e7 -I./.git/objects/cb -I./.git/objects/46 -I./.git/objects/79 -I./.git/objects/1e -I./.git/objects/24 -I./.git/objects/8d -I./.git/objects/76 -I./.git/objects/40 -I./.git/objects/7f -I./.git/info -I./.git/logs -I./.git/logs/refs -I./.git/logs/refs/heads -I./.git/logs/refs/remotes -I./.git/logs/refs/remotes/origin -I./.git/hooks -I./.git/refs -I./.git/refs/heads -I./.git/refs/tags -I./.git/refs/remotes -I./.git/refs/remotes/origin -I./Src -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -std=gnu11 -Wall --save-temps  -c Src/main.c -o Build/obj/./Src/main.o
ARM_SEMIHOSTING = Enable
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft --specs=rdimon.specs  -T stm32_linker_script.ld -Wl,-Map=main.map  Build/obj/./stm32_startup.o Build/obj/./Src/main.o -o Build/main.elf
```

## Running the application on the target

1. Connect the NUCLEOF446RE to the host machine via USB cable. It has a ST-LINK/V2-1 debugger and programmer on board and therefore doesn't require any external debugger to be connected.

2. Run openOCD application on the terminal and connect to the target

```shell
> openocd -f board/st_nucleo_f4.cfg

Open On-Chip Debugger 0.12.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
srst_only separate srst_nogate srst_open_drain connect_deassert_srst

Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : clock speed 2000 kHz
Info : STLINK V2J42M27 (API v2) VID:PID 0483:374B
Info : Target voltage: 3.246224
Info : [stm32f4x.cpu] Cortex-M4 r0p1 processor detected
Info : [stm32f4x.cpu] target has 6 breakpoints, 4 watchpoints
Info : starting gdb server for stm32f4x.cpu on 3333
Info : Listening on port 3333 for gdb connections
```

3. Run ARM gdb client (part of ARM GCC toolchain) and connect to the openocd server by giving "target remote localhost:3333" command, to be able to communicate with the target

```shell
> arm-none-eabi-gdb

GNU gdb (GNU Tools for STM32 11.3.rel1.20230519-1941) 12.1.90.20220802-git
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=x86_64-apple-darwin10 --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb) target remote localhost:3333
Remote debugging using localhost:3333
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x08000400 in ?? ()
(gdb) 
```

4. On the openocd console, we can see target is now connected to the gdb client

```shell
Open On-Chip Debugger 0.12.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
srst_only separate srst_nogate srst_open_drain connect_deassert_srst

Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : clock speed 2000 kHz
Info : STLINK V2J42M27 (API v2) VID:PID 0483:374B
Info : Target voltage: 3.246224
Info : [stm32f4x.cpu] Cortex-M4 r0p1 processor detected
Info : [stm32f4x.cpu] target has 6 breakpoints, 4 watchpoints
Info : starting gdb server for stm32f4x.cpu on 3333
Info : Listening on port 3333 for gdb connections
Info : accepting 'gdb' connection on tcp/3333
[stm32f4x.cpu] halted due to debug-request, current mode: Handler HardFault
xPSR: 0x81000003 pc: 0x08000400 msp: 0x2001ff70
Info : device id = 0x10006421
Info : flash size = 512 KiB
Info : flash size = 512 bytes
Warn : Prefer GDB command "target extended-remote :3333" instead of "target remote :3333"
```

5. Flash the application binary ("main.elf") onto the target by sending the following command through the gdb client

```shell
(gdb) monitor flash write_image erase documents/git/Task-Scheduler/build/main.elf
auto erase enabled
wrote 32768 bytes from file documents/git/Task-Scheduler/build/main.elf in 1.183492s (27.039 KiB/s)
```

5. Send the following set of commands via gdb client to reset the target and run the application

```shell
(gdb) monitor arm semihosting enable
semihosting is enabled
(gdb) monitor reset init
Unable to match requested speed 2000 kHz, using 1800 kHz
Unable to match requested speed 2000 kHz, using 1800 kHz
[stm32f4x.cpu] halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x080002fc msp: 0x20020000, semihosting
Unable to match requested speed 8000 kHz, using 4000 kHz
Unable to match requested speed 8000 kHz, using 4000 kHz
(gdb) monitor resume
(gdb)
```

6. We can view the prints on the openOCD console from which it is evident that different tasks are running in Round-Robin manner

```shell
Open On-Chip Debugger 0.12.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
srst_only separate srst_nogate srst_open_drain connect_deassert_srst

Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : clock speed 2000 kHz
Info : STLINK V2J42M27 (API v2) VID:PID 0483:374B
Info : Target voltage: 3.249376
Info : [stm32f4x.cpu] Cortex-M4 r0p1 processor detected
Info : [stm32f4x.cpu] target has 6 breakpoints, 4 watchpoints
Info : starting gdb server for stm32f4x.cpu on 3333
Info : Listening on port 3333 for gdb connections
[stm32f4x.cpu] halted due to breakpoint, current mode: Thread 
xPSR: 0x21000000 pc: 0x08001a9c msp: 0x2001ff00
Info : accepting 'gdb' connection on tcp/3333
Info : device id = 0x10006421
Info : flash size = 512 KiB
Info : flash size = 512 bytes
Warn : Prefer GDB command "target extended-remote :3333" instead of "target remote :3333"
Info : Unable to match requested speed 2000 kHz, using 1800 kHz
Info : Unable to match requested speed 2000 kHz, using 1800 kHz
[stm32f4x.cpu] halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x08000870 msp: 0x20020000, semihosting
Info : Unable to match requested speed 8000 kHz, using 4000 kHz
Info : Unable to match requested speed 8000 kHz, using 4000 kHz
Task1 Running
Task2 Running
Task2 Running
Task2 Running
Task2 Running
Task2 Running
Task2 Running
Task2 Running
Task2 Running
Task3 Running
Task3 Running
Task3 Running
...
...
```
