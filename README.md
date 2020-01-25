# CS120B_labs
Collection of labs for CS120B Intro to Embedded Systems
### Contributors:
* Ruth Navarrete (@ruth-navarrete)
* Dylan McDowell (@DylanMcDowell)

# Notes
* `ssh [username]@bolt.cs.ucr.edu` - to connect to UCR server
* `ssh wch136-0x` - where x is equal to 02-30, for direction connection to lab machines, need to be inside a UCR server initially before you can do this.
* `make test` - to generate and run tests for the program
* `make program` - Build the project and program the chip. (Don't forget to power the board). 
* `/usr/csshare/pkgs/cs120b-avrtools/createProject.sh` - runs project creation bash script
* `avr-gcc -mmcu=atmega1284 -I/usr/csshare/pkgs/simavr/ -Iheader/ -D_SIMULATE_ -Wall -Wl,--undefined=_mmcu,--section-start=.mmcu=910000 -o build/objects/main.elf source/main.c` - compiles the source into main.elf file
* `simavr -v -v -v -v -m atmega1284 -f 8000000 build/objects/main.elf` - runs simulation
* `gtkwave build/results/Lab2_introToAVR_trace.vcd` - runs waveform simulation
* `avrdude -c atmelice_isp -p atmega1284 -U hfuse:w:0xD9:m` - disable JTAG
* `tar -czvf [cslogin]_lab2.tgz turnin/` - to compress/zip turnin folder


# Lab Specifications
## LAB 2 - Intro to AVR Toolchain
#### Exercise 1
A garage door sensor connects to PA0 (1 means door open), and a light sensor connects to PA1 (1 means light is sensed). Program illuminates an LED connected to PB0 (1 means illuminate) if the garage door is open at night.

#### Exercise 2
Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning a car is parked in the space, of a four-space parking lot. Program outputs in binary on port C the number of available spaces.

#### Exercise 3
Extension of lab 2 exercise 2 program. Still writes the available spaces number, but only to PC3..PC0, and to set PC7 to 1 if the lot is full.

#### Exerise 4 (_CHALLENGE_)
An amusement park kid ride cart has three seats, with 8-bit weight sensors connected to ports A, B, and C (measuring from 0-255 kilograms). Set PD0 to 1 if the cart's total passenger weight exceeds the maximum of 140 kg. Also, the cart must be balanced: Set port PD1 to 1 if the difference between A and C exceeds 80 kg. Can you also devise a way to inform the ride operator of the approximate weight using the remaining bits on D?

(Hint: Use two intermediate variables to keep track of weight, one of the actual value and another being the shifted weight. Binary shift right by one is the same as dividing by two and binary shift left by one is the same as multiplying by two.)

## LAB 3 - Bit Manipulation
#### Exercise 1
Count the number of 1s on ports A and B and output that number on port C.

#### Exercise 2
A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. 

#### Exercise 3
In addition to the above, PA4 is 1 if a key is in the ignition, PA5 is one if a driver is seated, and PA6 is 1 if the driver's seatbelt is fastened. PC7 should light a "Fasten seatbelt" icon if a key is in the ignition, the driver is seated, but the belt is not fastened.

#### Exercise 4 (_CHALLENGE_)
Read an 8-bit value on PA7..PA0 and write that value on PB3..PB0PC7..PC4. That is to say,  take the upper nibble of PINA and map it to the lower nibble of PORTB, likewise take the lower nibble of PINA and map it to the upper nibble of PORTC (PA7 -> PB3, PA6 -> PB2, … PA1 -> PC5, PA0 -> PC4).

#### Exercise 5 (_CHALLENGE_)
(Challenge): A car's passenger-seat weight sensor outputs a 9-bit value (ranging from 0 to 511) and connects to input PD7..PD0PB0 on the microcontroller. If the weight is equal to or above 70 pounds, the airbag should be enabled by setting PB1 to 1. If the weight is above 5 but below 70, the airbag should be disabled and an "Airbag disabled" icon should light by setting PB2 to 1. (Neither B1 nor B2 should be set if the weight is 5 or less, as there is no passenger). 

## LAB 4 - State Machines
#### Exercise 1
PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's LED and turns on PB0's LED. 

#### Exercise 2
Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. Pressing PA0 increments PORTC once (stopping at 9). Pressing PA1 decrements PORTC once (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0.

#### Exercise 3
A household has a digital combination deadbolt lock system on the doorway. The system has buttons on a keypad. Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing and releasing '#', then pressing 'Y', should unlock the door by setting PB0 to 1. Any other sequence fails to unlock. Pressing a button from inside the house (PA7) locks the door (PB0=0). For debugging purposes, give each state a number, and always write the current state to PORTC (consider using the enum state variable). Also, be sure to check that only one button is pressed at a time. 

#### Exercise 4 (_CHALLENGE_)
Extend the above door (lab 4 part 3) so that it can also be locked by entering the earlier code.

#### Exercise 5 (_CHALLENGE_)
 Extend the above door (lab4 part 4) to require the 4-button sequence #-X-Y-X rather than the earlier 2-button sequence. To avoid excessive states, store the correct button sequence in an array, and use a looping SM. 

 ## LAB 5 - atmega1284chip (Hardware Light Display)
#### Exercise 1
(From an earlier lab) A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..C1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. Use buttons on PA3..PA0 and mimic the fuel-level sensor with presses.

[Video Demostration](http://youtu.be/_6BjqDXpdVk)

#### Exercise 2
(From an earlier lab) Buttons are connected to PA0 and PA1. Output for PORTC is initially 0. Pressing PA0 increments PORTC (stopping at 9). Pressing PA1 decrements PORTC (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0. If a reset occurs, both buttons should be fully released before additional increments or decrements are allowed to happen. Use LEDs (and resistors) on PORTC. Use a state machine (not synchronous) captured in C. 
* Note: Make sure that one button press causes only one increment or decrement respectively. Pressing and holding a button should NOT continually increment or decrement the counter.

[Video Demostration](http://youtu.be/a0cX_cjr5t0)

#### Exercise 3 (_CHALLENGE_)
(Challenge) Create your own festive lights display with 6 LEDs connected to port PB5..PB0, lighting in some attractive sequence. Pressing the button on PA0 changes the lights to the next configuration in the sequence.  Use a state machine (not synchronous) captured in C. 

[Video Demostration](http://youtu.be/ceOSKTxOP74)
