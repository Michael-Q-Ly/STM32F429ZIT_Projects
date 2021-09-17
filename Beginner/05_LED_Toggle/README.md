Modified Project 04 so that the LED would toggle on and off in an infinite loop containing a software delay.

The bitwise XOR with the correct mask will toggle the LED since 1^1 = 0, and 0^1 = 1! Pretty nifty trick.

Software delays can easily be performed by knowing the speed of the clock I'm using. I took an estimate and then
NOP'd for the software delay. I then changed the delay to what I thought was pleasing to look at physically.
