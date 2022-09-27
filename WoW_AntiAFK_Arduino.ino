
/* TEST AREA *PLACE CURSOR HERE WHEN LOADING CODE
 * 
 * w
 * ddda
 */

#include <Arduino.h>
#include <TrinketKeyboard.h>

unsigned long repeat_timer = 5000;
unsigned long last_repeat_time = 0;

unsigned long repeat_timer_min = 20000;
unsigned long repeat_timer_max = 90000;

unsigned long new_seed_timer = 60000;
unsigned long last_seed_update_time = 0;

unsigned long key_press_time_min = 400;
unsigned long key_press_time_max = 3500;


void dsm(unsigned long time_to_wait) {
  unsigned long started = millis();
  while(millis() - started <= time_to_wait) { /* just chill */ }
}

void setNewRandomSeed() {
  randomSeed(analogRead(1));
}

void performActionSingle(uint8_t key) {
  unsigned long key_press_time = random(key_press_time_min, key_press_time_max);
  TrinketKeyboard.pressKey(0, key);
  dsm(key_press_time);
  TrinketKeyboard.pressKey(0, 0);
}

void performActionMultiple(uint8_t key1, uint8_t key2) {
  unsigned long key_press_time = random(key_press_time_min, key_press_time_max);
  TrinketKeyboard.pressKey(0, key1);
  TrinketKeyboard.pressKey(0, key2); // IDK????
  dsm(key_press_time);
  TrinketKeyboard.pressKey(0, 0);
}


void move_diagnal_random() {
  // TODO
}

void move_straight_random() {
  int r = random(0, 4);

  uint8_t key;

  switch(r) {
    case(0):
      key = KEYCODE_D;
      break;
    case(1):
      key = KEYCODE_W;
      break;
    case(2):
      key = KEYCODE_A;
      break;
    case(3):
      key = KEYCODE_S;
      break;
    default:
      key = KEYCODE_C;
      break;
  }
 
  performActionSingle(key);
}

void move_fancy() {

}

void press_spacebar() {
  unsigned long key_press_time = random(80, 120);
  TrinketKeyboard.pressKey(0, KEYCODE_SPACE);
  dsm(key_press_time);
  TrinketKeyboard.pressKey(0, 0);
}

void setup() {
  TrinketKeyboard.begin();
}

void loop() {
  TrinketKeyboard.poll(); // must be done every ~10ms or computer will think device has stopped working

  if(millis() - last_seed_update_time >= new_seed_timer) {
    setNewRandomSeed();
    last_seed_update_time = millis();
  } 

  if(millis() - last_repeat_time >= repeat_timer) {
    unsigned long r = random(0, 3);

    if(r == 0) move_straight_random();
    else if(r == 1) move_straight_random();
    else if(r == 2) press_spacebar();

    repeat_timer = random(repeat_timer_min, repeat_timer_max);
    last_repeat_time = millis();

    TrinketKeyboard.pressKey(0, 0);
  }
}
