This is a sketch that turns an Arduino Leonardo (or similar) into a
keyboard controller for StepMania.  I built this as an update for
a metal dance stage that I first built for the PlayStation back in
December of 2002.

The pin definitions can be found inside the sketch, but basically
all IO pins are normally open switches.  Pins 1-4 are the arrow
keys for player 1.  Pin 5 is "ESC" for back, and 6 is "Enter" for
confirm.  Pins 8-11 are "WASD" keys for player 2 (by default
Stepmania uses the number pad for player 2, but the Arduino
keyboard library doesn't have constants for the number pad, and
this seemed like a reasonable compromise).

If you find this useful, please drop me a line and let me know.  :)
