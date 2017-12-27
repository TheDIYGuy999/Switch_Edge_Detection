/* Example sketch for switch edge detection and debouncing tutorial
    Based on: http://forum.arduino.cc/index.php?topic=301628.0 post #3
    Optimized by TheDIYGuy999, December 2017
*/

//
// =======================================================================================================
// PIN ASSIGNMENTS, MACROS & GLOBAL VARIABLES
// =======================================================================================================
//

// Button pins
#define BUTTON1 4

// LED pins
#define LED1 10

// macro for detection of rising edge and debouncing
/*the state argument (which must be a variable) records the current
  and the last 7 reads by shifting one bit to the left at each read.
  If the value is 15(=0b00001111) we have one rising edge followed by
  4 consecutive 1's. That would qualify as a debounced rising edge*/
#define DRE(signal, state) (state=(state<<1)|signal)==B00001111

// Rising state variables for each button
byte button1RisingState;

// macro for detection of falling edge and debouncing
/*the state argument (which must be a variable) records the current
  and the last 7 reads by shifting one bit to the left at each read.
  If the value is 240(=0b11110000) we have one falling edge followed by
  4 consecutive 0's. That would qualify as a debounced falling edge*/
#define DFE(signal, state) (state=(state<<1)|signal)==B11110000

// Falling state variables for each button
byte button1FallingState;

//
// =======================================================================================================
// MAIN ARDUINO SETUP (1x during startup)
// =======================================================================================================
//

void setup() {

  // Set pinmodes
  pinMode (BUTTON1, INPUT_PULLUP); // INPUT_PULLUP enables internal pullup resistor, so no external one is required!

  pinMode (LED1, OUTPUT); // Make LED pin an output

  // Start serial output
  Serial.begin (9600);
}

//
// =======================================================================================================
// READ BUTTONS
// =======================================================================================================
//

boolean readButtons() {

  // Read button states every 5 ms (debounce time):
  static unsigned long lastDebounce;
  if (millis() - lastDebounce >= 5) {
    lastDebounce = millis();

    // Rising edge (if switch is released)
    if (DRE(digitalRead(BUTTON1), button1RisingState)) {
      Serial.print ("Rising edge (pulled high by internal pullup resistor). State variable: ");
      Serial.println (button1RisingState);
    }

    // Falling edge (if switch is pressed)
    if (DFE(digitalRead(BUTTON1), button1FallingState)) {
      digitalWrite(LED1, !digitalRead(LED1)); // switch LED on or off
      Serial.print ("Falling edge (pulled low by switch). State variable: ");
      Serial.println (button1FallingState);
    }
  }
}

//
// =======================================================================================================
// MAIN LOOP
// =======================================================================================================
//

void loop() {

  // Read Buttons
  readButtons();
}

