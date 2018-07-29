#include <Keyboard.h>

/*
 * This is a sketch that turns an Arduino into a keyboard controller for StepMania.
 * 
 * The digital pins are configured as pullup inputs.  Pin 0 must not be connected to
 * ground for the keyboard to do anything; this is a safety precaution to make it so
 * we can kill the script if things go badly.  :)  The built in LED should be lit if
 * pin 0 is not jumpered.
 * 
 * Pins 1-10 are used for arrows for player 1 and player 2 (player 2 uses WASD as arrow 
 * keys).  Whenever a pin is connected to ground, the corresponding key will be pressed, 
 * and released when the pin is floating or high.
 */

#define KEY_COUNT 12 // Includes pin 0.
#define DEBOUNCE_DELAY_MS 10

uint8_t KEY_DEFS[KEY_COUNT] = {
  0, // Pin 0 is used to protect against runaway scripts.
  KEY_LEFT_ARROW,  // Pin  1 - P1 Left
  KEY_UP_ARROW,    // Pin  2 - P1 Up
  KEY_RIGHT_ARROW, // Pin  3 - P1 Right
  KEY_DOWN_ARROW,  // Pin  4 - P1 Down
  KEY_ESC,         // Pin  5 - Back
  KEY_RETURN,      // Pin  6 - Confirm
  KEY_F1,          // Pin  7 - Coin
  'a',             // Pin  8 - P2 Left
  'w',             // Pin  9 - P2 Up
  'd',             // Pin 10 - P2 Right
  's'              // Pin 11 - P2 Down
};

bool pressed[KEY_COUNT + 1];
unsigned long lastChange[KEY_COUNT + 1];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  // Set pins 0-KEY_COUNT as INPUT_PULLUP.
  // Note that we don't use pin 13 as on most boards it has an LED an a built in resistor.
  for(int i = 0; i <= KEY_COUNT; i++) {
    pinMode(i, INPUT_PULLUP);

    pressed[i] = HIGH;
    lastChange[i] = 0;
  }
}

void loop() {
  int val;
  
  // If pin 0 is not connected to ground, then do nothing - this is to make it easier
  // to flash a misbehaving script.
  val = digitalRead(0);

  // LED indicates if we are working.
  digitalWrite(LED_BUILTIN, !val ? LOW : HIGH);

  if(val == LOW) {
    delay(1000);
    return;
  }

  unsigned long now = millis();

  // Sample each key
  for(int i = 1; i <= KEY_COUNT; i++) {
    val = digitalRead(i);
    bool isPressed = val == LOW;

    // Debounce keys
    bool canChange = now > (lastChange[i] + DEBOUNCE_DELAY_MS);

    if(canChange && pressed[i] != isPressed) {
      pressed[i] = isPressed;
      lastChange[i] = now;
      if(isPressed) {
        Keyboard.press(KEY_DEFS[i]);
      } else {
        Keyboard.release(KEY_DEFS[i]);
      }
    }
  }

}
