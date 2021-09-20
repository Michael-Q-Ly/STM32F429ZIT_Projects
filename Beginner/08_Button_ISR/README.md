This program uses a hardware ISR and an optimization level 3.
The program uses a button and counts how many time you press the button on the
Discovery 1 board. The button uses a software delay to debounce.

The base program does not contain the volatile keyword and we are to optimize at level 3.
What changes can we make to ensure the code runs correctly?

Well.. we know that we count button presses, so this has to be volatile: the user
changes the value of the counter.

We also know that the addresses of our internal registers must be volatile. Why?
That's basic. It's because the contents of the registers can change. We will have
to SET certain bits to enable clocks, GPIO, etc.
