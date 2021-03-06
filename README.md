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
* `tar -czvf [cslogin]_lab[lab_number].tgz turnin/` - to compress/zip turnin folder


# Lab Specifications
### LAB 2 - Intro to AVR Toolchain
#### Exercise 1
A garage door sensor connects to PA0 (1 means door open), and a light sensor connects to PA1 (1 means light is sensed). Program illuminates an LED connected to PB0 (1 means illuminate) if the garage door is open at night.

#### Exercise 2
Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning a car is parked in the space, of a four-space parking lot. Program outputs in binary on port C the number of available spaces.

#### Exercise 3
Extension of lab 2 exercise 2 program. Still writes the available spaces number, but only to PC3..PC0, and to set PC7 to 1 if the lot is full.

#### Exerise 4 (_CHALLENGE_)
An amusement park kid ride cart has three seats, with 8-bit weight sensors connected to ports A, B, and C (measuring from 0-255 kilograms). Set PD0 to 1 if the cart's total passenger weight exceeds the maximum of 140 kg. Also, the cart must be balanced: Set port PD1 to 1 if the difference between A and C exceeds 80 kg. Can you also devise a way to inform the ride operator of the approximate weight using the remaining bits on D?

### LAB 3 - Bit Manipulation
#### Exercise 1
Count the number of 1s on ports A and B and output that number on port C.

#### Exercise 2
A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. 

#### Exercise 3
In addition to the above, PA4 is 1 if a key is in the ignition, PA5 is one if a driver is seated, and PA6 is 1 if the driver's seatbelt is fastened. PC7 should light a "Fasten seatbelt" icon if a key is in the ignition, the driver is seated, but the belt is not fastened.

#### Exercise 4 (_CHALLENGE_)
Read an 8-bit value on PA7..PA0 and write that value on PB3..PB0PC7..PC4. That is to say,  take the upper nibble of PINA and map it to the lower nibble of PORTB, likewise take the lower nibble of PINA and map it to the upper nibble of PORTC (PA7 -> PB3, PA6 -> PB2, … PA1 -> PC5, PA0 -> PC4).

#### Exercise 5 (_CHALLENGE_)
A car's passenger-seat weight sensor outputs a 9-bit value (ranging from 0 to 511) and connects to input PD7..PD0PB0 on the microcontroller. If the weight is equal to or above 70 pounds, the airbag should be enabled by setting PB1 to 1. If the weight is above 5 but below 70, the airbag should be disabled and an "Airbag disabled" icon should light by setting PB2 to 1. (Neither B1 nor B2 should be set if the weight is 5 or less, as there is no passenger). 

### LAB 4 - State Machines
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

### LAB 5 - atmega1284chip (Hardware Light Display)
#### Exercise 1
(From an earlier lab) A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..C1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. Use buttons on PA3..PA0 and mimic the fuel-level sensor with presses.

#### Exercise 2
(From an earlier lab) Buttons are connected to PA0 and PA1. Output for PORTC is initially 0. Pressing PA0 increments PORTC (stopping at 9). Pressing PA1 decrements PORTC (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0. If a reset occurs, both buttons should be fully released before additional increments or decrements are allowed to happen. Use LEDs (and resistors) on PORTC. Use a state machine (not synchronous) captured in C. 
* Note: Make sure that one button press causes only one increment or decrement respectively. Pressing and holding a button should NOT continually increment or decrement the counter.

#### Exercise 3 (_CHALLENGE_)
Create your own festive lights display with 6 LEDs connected to port PB5..PB0, lighting in some attractive sequence. Pressing the button on PA0 changes the lights to the next configuration in the sequence.  Use a state machine (not synchronous) captured in C. 

### LAB 6 - SynchSMs
#### Exercise 1
Create a synchSM to blink three LEDs connected to PB0, PB1, and PB2 in sequence, 1 second each.

#### Exercise 2
Create a simple light game that requires pressing a button on PA0 while the middle of three LEDs on PB0, PB1, and PB2 is lit. The LEDs light for 300 ms each in sequence. When the button is pressed, the currently lit LED stays lit. Pressing the button again restarts the game.

#### Exercise 3 (_CHALLENGE_)
(from an earlier lab) Buttons are connected to PA0 and PA1. Output for PORTB is initially 7. Pressing PA0 increments PORTB once (stopping at 9). Pressing PA1 decrements PORTB once (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTB resets to 0. Now that we have timing, only check to see if a button has been pressed every 100 ms. Additionally, if a button is held, then the count should continue to increment (or decrement) at a rate of once per second.

### LAB 7 - LCD Screen
#### Exercise 1
Buttons are connected to PA0 and PA1. Output PORTC and PORTD drive the LCD display, initially displaying 0. Pressing PA0 increments the display (stopping at 9). Pressing PA1 decrements the display (stopping at 0). If both buttons are depressed (even if not initially simultaneously), the display resets to 0. If a button is held, then the display continues to increment (or decrement) at a rate of once per second. Use a synchronous state machine captured in C.
* Note: The LCD display displays ASCII values so 9 is not the same as ‘9’. For displaying numbers 0 thru 9, a quick conversion technique is to add the character ‘0’ to the number.

#### Exercise 2 (_CHALLENGE_)
Extend the earlier light game to maintain a score on the LCD display. The initial score is 5. Each time the user presses the button at the right time, the score increments. Each time the user fails, the score decrements. When reaching 9, show victory somehow. 

### LAB 8 - A2D (light meter)
#### Exercise 1
The potentiometer is used to adjust the voltage supplied to the microcontroller for ADC . Design a system that reads the 10-bit ADC result from the ADC register, and displays the result on a bank of 10 LEDs.

#### Exercise 2
A photoresistor is a resistor whose resistance varies based on how much light the photoresistor detects. An additional resistor needs to be connected in parallel with the photoresistor. Without the additional resistor, results from ADC will be too small to observe. A 330 ohm resistor is chosen because it is common in the lab kits. Connect the photoresistor to the microcontroller according to the diagram below.

#### Exercise 3
Design a system where an LED is illuminated only if enough light is detected from the photo resistor. Criteria:
* If the result of the ADC is >= MAX/2, the LED is illuminated.
* If the result of the ADC is < MAX/2, the LED is turned off.

#### Exercise 4 (_CHALLENGE_)
Design a system, using a bank of eight LEDs, where the number of LEDs illuminated is a representation of how much light is detected. For example, when more light is detected, more LEDs are illuminated. Criteria:
* The LEDs should illuminated in sequence from 0 to 7, based on the amount of light detected by the photoresistor.

### LAB 9 - PWM (music player)
#### Exercise 1
Using the ATmega1284’s PWM functionality, design a system that uses three buttons to select one of three tones to be generated on the speaker. When a button is pressed, the tone mapped to it is generated on the speaker. Criteria:
* Use the tones C4, D4, and E4 from the table in the introduction section.
* When a button is pressed and held, the tone mapped to it is generated on the speaker.
* When more than one button is pressed simultaneously, the speaker remains silent. 
* When no buttons are pressed, the speaker remains silent.

#### Exercise 2
Using the ATmega1284’s PWM functionality, design a system where the notes: C4, D, E, F, G, A, B, and C5,  from the table at the top of the lab, can be generated on the speaker by scaling up or down the eight note scale. Three buttons are used to control the system. One button toggles sound on/off. The other two buttons scale up, or down, the eight note scale. Criteria:
* The system should scale up/down one note per button press.
* When scaling down, the system should not scale below a C.
* When scaling up, the system should not scale above a C.

#### Exercise 3 (_CHALLENGE_)
Using the ATmega1284’s built in PWM functionality, design a system where a short, five-second melody, is played when a button is pressed. NOTE: The melody must be somewhat complex (scaling from C to B is NOT complex). Criteria:
* When the button is pressed, the melody should play until completion
* Pressing the button again in the middle of the melody should do nothing
* If the button is pressed and held, when the melody finishes, it should not repeat until the button is released and pressed again

### LAB 10 - Concurrent synchSMs
#### Exercise 1
Connect LEDs to PB0, PB1, PB2, and PB3. 
* In one state machine (ThreeLEDsSM), output to a shared variable (threeLEDs) the following behavior: set only bit 0 to 1, then only bit 1, then only bit 2 in sequence for 1 second each. 
* In a second state machine (BlinkingLEDSM), output to a shared variable (blinkingLED) the following behavior: set bit 3 to 1 for 1 second, then 0 for 1 second. 
* In a third state machine (CombineLEDsSM), combine both shared variables and output to the PORTB. 

#### Exercise 2
Modify the above example so the threeLEDs light for 300 ms, while blinkingLED’s LED still blinks 1 second on and 1 second off.

#### Exercise 3
To the previous exercise's implementation, connect your speaker's red wire to PB4 and black wire to ground. Add a third task that toggles PB4 on for 2 ms and off for 2 ms as long as a switch on PA2 is in the on position. Don’t use the PWM for this task.

#### Exercise 4 (_CHALLENGE_)
Extend the previous exercise to allow a user to adjust the sound frequency up or down using buttons connected to PA0 (up) and PA1 (down). Using our 1 ms timer abstraction, the fastest you'll be able to pulse is 1 ms on and 1 ms off, meaning 500 Hz.

### LAB 11 - Scheduler (scrolling game)
#### Exercise 1
Modify the keypad code to be in an SM task. Then, modify the keypad SM to utilize the simple task scheduler format. All code from here on out should use the task scheduler.

#### Exercise 2
Use the LCD code, along with a button and/or time delay to display the message "CS120B is Legend... wait for it DARY!" The string will not fit on the display all at once, so you will need to come up with some way to paginate or scroll the text.

#### Exercise 3
Combine the functionality of the keypad and LCD so when keypad is pressed and released, the character of the button pressed is displayed on the LCD, and stays displayed until a different button press occurs (May be accomplished with two tasks: LCD interface & modified test harness).

#### Exercise 4 (_CHALLENGE_)
Notice that you can visually see the LCD refresh each character (display a lengthy string then update to a different lengthy string). Design a system where a single character is updated in the displayed string rather than the entire string itself. Use the functions provided in “io.c”.

An example behavior would be to initially display a lengthy string, such as “Congratulations!”. The first keypad button pressed changes the first character ‘C’ to the button pressed. The second keypad press changes the second character to the second button pressed, etc. No refresh should be observable during the character update.

#### Exercise 4 (_CHALLENGE_)
Using both rows of the LCD display, design a game where a player controlled character avoids oncoming obstacles. Three buttons are used to operate the game. Criteria:
* Use the cursor as the player controlled character.
* Choose a character like ‘#’, ‘*’, etc. to represent the obstacles.
* One button is used to pause/start the game.
* Two buttons are used to control the player character. One button moves the player to the top row. The other button moves the player to the bottom row.
* A character position change should happen immediately after pressing the button.
* Minimum requirement is to have one obstacle on the top row and one obstacle on the bottom row. You may add more if you are feeling up to the challenge.
* Choose a reasonable movement speed for the obstacles (100ms or more).
* If an obstacle collides with the player, the game is paused, and a “game over” message is displayed. The game is restarted when the pause button is pressed.
