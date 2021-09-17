A reintroduction to pointers in C.

I had to look at the datasheet of my MCU to do this assignment.

I first turn on the peripheral clock after obtaining its address and address offset.

Next, I enable the LED by looking at the schematic and seeing that it is memory mapped to Port G.
Thus, I enable Port G's clock.

From there, I configure the correct pin for output and clear the bit positions to get them into a known state.
I then set the bit position

Lastly, I set the output pin that the LED is mapped to high.

The program is then NOP'd forever.

I single-stepped through this and viewed the SFR's in the IDE I used (STM32Cube).
This way, I could see how each of my actions above was physically implemented in the device to
lead up to the LED blinking.

Very satisfying!
