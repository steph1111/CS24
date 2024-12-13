/**
 * CS24: Second Arduino Lab
 * @authors Liam Gilligan and Stephanie L'Heureux
 * 
 * It's not a bomb countdown timer
 * Timer with range 0.0s to 9.9s, adjustable by rotary encoder.
 */

// Pin constants:
// 7-segment display 74HC595 1 (left)
const int latch_1 = 13; // ST_CP of 74HC595
const int data_1  = 12; // DS of 74HC595
const int clock_1 = 11; // SH_CP of 74HC595
// 7-segment display 74HC595 0 (right)
const int latch_0 = 10; // ST_CP of 74HC595
const int data_0  = 9;  // DS of 74HC595
const int clock_0 = 8;  // SH_CP of 74HC595 
// Rot(ary) encoder
const int rot_sw  = 7;  // Button rotary encoder
const int rot_dt  = 6;  // DT of rotary encoder
const int rot_clock = 5;// CLK of rotary encoder

// Other globals:
int rot_rotation  = 0; // Track the rotation of the rot
int rotating = 0;
bool rotation_mode = true;
int max_time = 0;
// Integer to 7-bit display
int int_to_seg[10] = {
  0b11111100, // 0
  0b01100000, // 1
  0b11011010, // 2
  0b11110010, // 3
  0b01100110, // 4
  0b10110110, // 5
  0b10111110, // 6
  0b11100000, // 7
  0b11111110, // 8
  0b11110110, // 9
};

/**
 * Initialize pin modes of each pin. 
 */
void setup () {
  pinMode(latch_1,  OUTPUT);
  pinMode(data_1, OUTPUT);
  pinMode(clock_1, OUTPUT);
  
  pinMode(latch_0,  OUTPUT);
  pinMode(data_0, OUTPUT);
  pinMode(clock_0, OUTPUT);
  
  pinMode(rot_sw, INPUT);
  pinMode(rot_dt, INPUT);
  pinMode(rot_clock, INPUT);
  digitalWrite(rot_sw, HIGH);
  // Start displaying 0.0
  display_value(0);
}

/**
 * Program body.
 */
void loop() {
  // Update rotating state based on rotation mode
  if (rotation_mode) {
    rotating = check_rot_rotation();
  }

  // if button was pressed and in rotation mode, enter countdown mode
  if (digitalRead(rot_sw) == LOW && rotation_mode) {
    rotation_mode = false;
  }

  if (rotation_mode) {
    if (rotating) {
      increment_max_time(rotating);
      display_value(max_time);
    }
  } else {
    if (max_time <= 0) {
      display_value(0);
      delay_and_check_for_rotation(1000);
      display_none();
      delay_and_check_for_rotation(1000);
    } else {
      display_value(max_time);
      max_time--;
      // / delay 0.1 second while looking for rotation
      delay_and_check_for_rotation(100);
    }
  }
}

/**
 * Check if rotary encoder has been rotated, and if so, which direction.
 * 
 * @return 1 if rotated clockwise, -1 if rotated counter clockwise, 0 if not rotated.
 */
int check_rot_rotation () {
  static int old_clk = HIGH;
  static int old_dt = HIGH;
  int result = 0;
  int clk_read = digitalRead(rot_clock);
  int dt_read = digitalRead(rot_dt);
  
  // if value of rot_dt or rot_clock has changed since the last read
  if (clk_read != old_clk || dt_read != old_dt) {
    if (old_clk == HIGH && clk_read == LOW) {
      result = (old_dt * 2 - 1);
    }
  }
  // track last read
  old_clk = clk_read;
  old_dt = dt_read;
  return result;
}

/**
 * Display number on seven seven segment displays. Number displayed
 * is the first digit of `value` dot second digit of `value`.
 * 
 * @param value Number to display.
 */
void display_value (int value) {
  digitalWrite(latch_1, LOW);
  digitalWrite(latch_0, LOW);

  // Extract last digit, convert to 7-segment bin representation and display
  shiftOut(data_0, clock_0, MSBFIRST, int_to_seg[value % 10]);
  // Extract first digit, convert to 7-segment bin representation (with a decimal) and display
  shiftOut(data_1, clock_1, MSBFIRST, int_to_seg[value / 10] | 1);

  digitalWrite(latch_1, HIGH);
  digitalWrite(latch_0, HIGH);
}

/**
 * Increments `max_time` based on the value of `rotation`. Does
 * not increment if the value would exceed 99, or fall below 0.
 * 
 * @param rotation Value to increment by. (1 or -1).
 */
void increment_max_time(int rotation) {
  if ((max_time != 0 || rotation > 0) && (max_time != 99 || rotation < 0)) {
    max_time += rotation;
  }
}

/**
 * Delays program while still checking for encoder rotation.
 * 
 * @param wait Total time to wait if not interupted.
 */
void delay_and_check_for_rotation(int wait) {
  for (int i = 0; i < wait; i++) {
    delay(1);
    if (check_rot_rotation()) {
      rotating = true;
      rotation_mode = true;
      return;
    }
  }
}

/**
 * Sets the 7-segment displays to display nothing.
 */
void display_none () {
  digitalWrite(latch_1, LOW);
  digitalWrite(latch_0, LOW);

  shiftOut(data_0, clock_0, MSBFIRST, 0);
  shiftOut(data_1, clock_1, MSBFIRST, 0);

  digitalWrite(latch_1, HIGH);
  digitalWrite(latch_0, HIGH);
}