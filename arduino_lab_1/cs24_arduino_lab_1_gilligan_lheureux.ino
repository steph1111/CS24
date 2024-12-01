#include <string.h>
#define BUTTON 9

String liam = "liam";
String steph = "steph";

int* charbin(char c) {
  int* bin = new int[7];
  for (int i = 0; i < 7; i++) {
    bin[i] = c & 1;
    c >>= 1;
  }
  return bin;
}

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

void wait_for_button() {
  bool lastValue = 1;
  bool value = 1;
  while(!value || lastValue) {
    lastValue = value;
    value = digitalRead(BUTTON);
  }
}

void set_low() {
  for (int i = 2; i < 9; i++) {
    digitalWrite(i, LOW);
  }
}

void setup() {
  for (int i = 2; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON, INPUT);
}

void loop() {
  display_name(liam);
  set_low();
  wait_for_button();
  display_name(steph);
  set_low();
  wait_for_button();
}
