// TV Type 2.0
// Roni Bandini, June 2026, MIT License
// RCA Yellow D7, Brown D9
// 3 Fermion AdKey connected to A3, A4, A5

#include <TVout.h>
#include <font6x8.h>
#include "logo.h"

#define ADPIN  A3
#define ADPIN2 A4
#define ADPIN3 A5
#define myLed  2

#define CHAR_W   6
#define CHAR_H   8
#define MARGIN_Y 22
#define MAX_X    120
#define MAX_Y    88

const int percentageVariation = 8;
const int totalKeys = 10;
const int targetReadings[totalKeys] = {133, 240, 327, 450, 585, 660, 785, 920, 1014, 0};

// "del" and "space" are handled aside
const char* keypad1[totalKeys] = {"Q", "W", "E", "P", "A", "S", "L", "Z", "X", "space"};
const char* keypad2[totalKeys] = {"R", "T", "Y", "D", "F", "G", "C", "V", "B", "del"};
const char* keypad3[totalKeys] = {"U", "I", "O", "H", "J", "K", "N", "M", ".", "?"};

TVout tv;

int cursorX = 0;
int cursorY = MARGIN_Y;

void cursorAdvance() {
  cursorX += CHAR_W;
  if (cursorX > MAX_X) {
    cursorX = 0;
    cursorY += CHAR_H;
  }
  if (cursorY > MAX_Y) {
    tv.clear_screen();
    printHeader();
    cursorX = 0;
    cursorY = MARGIN_Y;
  }
}

void cursorBack() {
  cursorX -= CHAR_W;
  if (cursorX < 0) {
    cursorY -= CHAR_H;
    if (cursorY < MARGIN_Y) {
      cursorY = MARGIN_Y;
    }
    cursorX = MAX_X;
  }
}

void printHeader() {
  tv.print(0, 0,  "TV TYPE");
  tv.print(0, 10, "-------");
}

const char* mapReading(int reading, const char* keypad[]) {
  if (reading == 1023) return "NONE";

  int tolerance = (1023 * percentageVariation) / 100;
  for (int i = 0; i < totalKeys; i++) {
    if (i == 8) {
      if (reading >= 1010 && reading <= 1022) return keypad[i];
    } else {
      if (abs(reading - targetReadings[i]) <= tolerance) return keypad[i];
    }
  }
  return "NONE";
}

void processKey(const char* key) {
  if (strcmp(key, "NONE") == 0) return;

  if (strcmp(key, "space") == 0) {
    cursorAdvance();
    delay(250);
    return;
  }

  if (strcmp(key, "del") == 0) {
    cursorBack();
    tv.set_cursor(cursorX, cursorY);
    tv.print(' ');
    delay(250);
    return;
  }

  tv.set_cursor(cursorX, cursorY);
  tv.print(key[0]);
  cursorAdvance();
  delay(250);
}

void setup() {
  pinMode(myLed, OUTPUT);
  digitalWrite(myLed, HIGH);

  tv.begin(NTSC, 128, 96);
  tv.bitmap(1, 20, Logo);
  tv.delay(3000);

  tv.select_font(font6x8);
  tv.clear_screen();
  
  tv.print(0, 16, "The TV Typewriter");
  tv.delay(1000);
  tv.print(0, 24, "was a 1973 project");
  tv.delay(1000);
  tv.print(0, 32, "that turned a home");
  tv.delay(1000);
  tv.print(0, 40, "TV into a type-");
  tv.delay(1000);
  tv.print(0, 48, "writer. This project");
  tv.delay(1000);
  tv.print(0, 56, "is a tribute using");
  tv.delay(1000);
  tv.print(0, 64, "Arduino");
  tv.delay(1000);
  tv.print(0, 72, " -Roni Bandini 6/26");
  
  tv.delay(5000);
  
  tv.clear_screen();
  printHeader();

  digitalWrite(myLed, LOW);
}

void loop() {
  analogRead(ADPIN);  delay(2);
  processKey(mapReading(analogRead(ADPIN),  keypad1));

  analogRead(ADPIN2); delay(2);
  processKey(mapReading(analogRead(ADPIN2), keypad2));

  analogRead(ADPIN3); delay(2);
  processKey(mapReading(analogRead(ADPIN3), keypad3));
}