# Lab4_stateMachines
Lab 4 for CS120B Intro to Embedded Systems

### Exercise 1
PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's LED and turns on PB0's LED. 

### Exercise 2
Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. Pressing PA0 increments PORTC once (stopping at 9). Pressing PA1 decrements PORTC once (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0.

### Exercise 3
A household has a digital combination deadbolt lock system on the doorway. The system has buttons on a keypad. Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing and releasing '#', then pressing 'Y', should unlock the door by setting PB0 to 1. Any other sequence fails to unlock. Pressing a button from inside the house (PA7) locks the door (PB0=0). For debugging purposes, give each state a number, and always write the current state to PORTC (consider using the enum state variable). Also, be sure to check that only one button is pressed at a time. 

# Notes
* `ssh [username]@bolt.cs.ucr.edu` - to connect to UCR server
* `ssh wch136-0x` - where x is equal to 02-30, for direction connection to lab machines, need to be inside a UCR server initially before you can do this.
* `make test` - to generate and run tests for the program
* `/usr/csshare/pkgs/cs120b-avrtools/createProject.sh` - runs project creation bash script
* `avr-gcc -mmcu=atmega1284 -I/usr/csshare/pkgs/simavr/ -Iheader/ -D_SIMULATE_ -Wall -Wl,--undefined=_mmcu,--section-start=.mmcu=910000 -o build/objects/main.elf source/main.c` - compiles the source into main.elf file
* `simavr -v -v -v -v -m atmega1284 -f 8000000 build/objects/main.elf` - runs simulation
* `gtkwave build/results/Lab2_introToAVR_trace.vcd` - runs waveform simulation
* `avrdude -c atmelice_isp -p atmega1284 -U hfuse:w:0xD9:m` - disable JTAG
