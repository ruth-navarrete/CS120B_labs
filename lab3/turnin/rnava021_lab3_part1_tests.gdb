# Test file for Lab3_bitManip


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
# # Set inputs
# Continue for several ticks
# Set expect values
# Check pass/fail

# Add tests below
test "PINA: 0x00, PINB: oxoo => PORTC: 0x00"
setPINA 0x00
setPINB 0x00
continue 5
expectPORTC 0x00
checkResult

test "PINA: 0x01, PINB: 0x00 => PORTC: 0x01"
setPINA 0x01
setPINB 0x00
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x02, PINB: 0x00 => PORTC: 0x01"
setPINA 0x02
setPINB 0x00
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x03, PINB: 0x00 => PORTC: 0x02"
setPINA 0x03
setPINB 0x00
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x04, PINB: 0x00 => PORTC: 0x01"
setPINA 0x04
setPINB 0x00
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x05, PINB: 0x00 => PORTC: 0x02"
setPINA 0x05
setPINB 0x00
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x06, PINB: 0x00 => PORTC: 0x02"
setPINA 0x06
setPINB 0x00
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x07, PINB: 0x00 => PORTC: 0x03"
setPINA 0x07
setPINB 0x00
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x08, PINB: 0x00 => PORTC: 0x01"
setPINA 0x08
setPINB 0x00
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x09, INB: 0x00 => PORTC: 0x02"
setPINA 0x09
setPINB 0x00
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x0A, PINB 0x00 => PORTC: 0x02"
setPINA 0x0A
setPINB 0x00
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x0B, PINB 0x00 => PORTC: 0x03"
setPINA 0x0B
setPINB 0x00
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x0C, PINB: 0x00 => PORTC: 0x02"
setPINA 0x0C
setPINB 0x00
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x0D, PINB: 0x00 => PORTC: 0x003"
setPINA 0x0D
setPINB 0x00
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x0E, PINB: 0x00 => PORTC: 0x03"
setPINA 0x0E
setPINB 0x00
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x0F, PINB: 0x00 => PORTC: 0x04"
setPINA 0x0F
setPINB 0x00
continue 5
expectPORTC 0x04
checkResult

test "PINA: 0x00, PINB: 0x01 => PORTC: 0x01"
setPINA 0x00
setPINB 0x01
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x00, PINB: 0x02 => PORTC: 0x01"
setPINA 0x00
setPINB 0x02
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x00, PINB: 0x03 => PORTC: 0x02"
setPINA 0x00
setPINB 0x03
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x00, PINB: 0x04 => PORTC: 0x01"
setPINA 0x00
setPINB 0x04
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x00, PINB: 0x05 => PORTC: 0x02"
setPINA 0x00
setPINB 0x05
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x00, PINB: 0x06 => PORTC: 0x02"
setPINA 0x00
setPINB 0x06
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x00, PINB: 0x07 => PORTC: 0x03"
setPINA 0x00
setPINB 0x07
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x00, PINB: 0x08 => PORTC: 0x01"
setPINA 0x00
setPINB 0x08
continue 5
expectPORTC 0x01
checkResult

test "PINA: 0x00, PINB: 0x09 => PORTC: 0x02"
setPINA 0x00
setPINB 0x09
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x00, PINB: 0x0A => PORTC: 0x02"
setPINA 0x00
setPINB 0x0A
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x00, PINB: 0x0B => PORTC: 0x03"
setPINA 0x00
setPINB 0x0B
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x00, PINB: 0x0C => PORTC: 0x02"
setPINA 0x00
setPINB 0x0C
continue 5
expectPORTC 0x02
checkResult

test "PINA: 0x00, PINB: 0x0D => PORTC: 0x03"
setPINA 0x00
setPINB 0x0D
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x00, PINB: 0x0E => PORTC: 0x03"
setPINA 0x00
setPINB 0x0E
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0x00, PINB: 0x0F => PORTC: 0x04"
setPINA 0x00
setPINB 0x0F
continue 5
expectPORTC 0x04
checkResult

test "PINA: 0x00, PINB: 0xFF => PORTC: 0x08"
setPINA 0x00
setPINB 0xFF
continue 5
expectPORTC 0x08
checkResult

test "PINA: 0xFF, PINB: 0x00 => PORTC: 0x08"
setPINB 0x00
setPINA 0xFF
continue 5
expectPORTC 0x08
checkResult

test "PINA: 0xF0, PINB 0x01 => PORTC: 0x05"
setPINB 0x01
setPINA 0xF0
continue 5
expectPORTC 0x05
checkResult

test "PINA: 0x03, PINB: 0x02 => PORTC: 0x03"
setPINB 0x02
setPINA 0x03
continue 5
expectPORTC 0x03
checkResult

test "PINA: 0xA0, PINB 0x03 => PORTC: 0x04"
setPINB 0x03
setPINA 0xA0
continue 5
expectPORTC 0x04
checkResult

test "PINA: 0xF0, PINB: 0xF4 => PORTC: 0x09"
setPINB 0xF4
setPINA 0xF0
continue 5
expectPORTC 0x09
checkResult

test "PINA: 0xFF, PINB: 0x05 => PORTC: 0x0A"
setPINB 0x05
setPINA 0xFF
continue 5
expectPORTC 0x0A
checkResult

test "PINA: 0xCC, PINB: 0x06 => PORTC: 0x06"
setPINB 0x06
setPINA 0xCC
continue 5
expectPORTC 0x06
checkResult

test "PINA: 0xFF, PINB: 0xFF => PORTC: 0x10"
setPINB 0xFF
setPINA 0xFF
continue 5
expectPORTC 0x10
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n