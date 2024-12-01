/**
 * CS24: First Arduino Lab
 * @authors Liam Gilligan and Stephanie L'Heureux
 * 
 * Your name in lights.
 * Lights up seven LEDs in a pattern comprising of the seven least 
 * significant bits of the ascii values in the letters of lab partners 
 * names followed by a "space" (indicated by all lights off.)
 */
#include <string.h>

#define BUTTON 9
String liam = "liam";
String steph = "steph";

/**
 * Converts a character to binary.
 * 
 * @param c Charater to convert.
 * @return Integer pointer to a heap allocated integer array containing
 * seven elements, each either 1 or 0, representing the bits of the ASCII
 * representation of the input character `c`.
 */
int* charbin(char c) {
  int* bin = new int[7];
  for (int i = 0; i < 7; i++) {
    bin[i] = c & 1;
    c >>= 1;
  }
  return bin;
}

/**
 * Lights up a sequence of seven LEDs (pins 2-8) encoding the input parameter
 * `name` as a pattern in which each character of `name` is displayed as 
 * he least significant bits of its ASCII value. Characters are advanced
 * by button press.
 * 
 * @param name String to display in lights.
 */
void display_name(String name) {
  for (int i = 0; i < name.length(); i++) {
    int* bin = charbin(name[i]);
    for(int j = 0; j < 7; j++) {
      digitalWrite(j + 2, bin[j]);
    }
    wait_for_button();
    delete[] bin;
  }
}

/**
 * Delays execution until button has been pressed.
 */
void wait_for_button() {
  bool lastValue = digitalRead(BUTTON);
  bool value = digitalRead(BUTTON);
  while(!value || lastValue) {
    lastValue = value;
    value = digitalRead(BUTTON);
  }
}

/**
 * Sets all LEDs (pins 2-8) to LOW, turning them off.
 */
void set_low() {
  for (int i = 2; i < 9; i++) {
    digitalWrite(i, LOW);
  }
}

/**
 * Initialize pin modes of each pin. 
 */
void setup() {
  for (int i = 2; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON, INPUT);
}

/**
 * Loop body.
 */
void loop() {
  display_name(liam);
  set_low();
  wait_for_button();
  display_name(steph);
  set_low();
  wait_for_button();
}
