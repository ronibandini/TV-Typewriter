// TV Typewriter 
// Roni Bandini, March 2026, MIT License

// Notes: Sync to D7, Video to D9, Keypad to A0- Copy TVOut font folder to Arduino libraries folder before uploading

#include <TVout.h>
#include <font6x8.h>

// Keypad config
#define RESOLUTION 10
#define MAXVALUE 1024 
#define PRECISION 15   
#define ADPIN A0

TVout TV;
uint32_t ADKeyVal[10] = {0};
uint32_t ADCKeyIn = 0;

int cursorX = 0;
int cursorY = 32; 

// lowest button is K0 -> J
char keyMap[10] = {'J','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

void setup() {
  TV.begin(NTSC, 128, 96);
  TV.select_font(font6x8);
  
  TV.clear_screen();
  TV.print(0, 0, "TV TYPEWRITER");
  TV.print(0, 10, "RONI BANDINI 3/26");
  TV.print(0, 20, "-----------------");
  
  ADKeybegin();
}

void loop() {
  ADCKeyIn = analogRead(ADPIN);

  if (ADCKeyIn < (MAXVALUE - PRECISION)) {
    int8_t keyIndex = getKey();
    
    if (keyIndex != -1) {
      char keyChar = keyMap[keyIndex];
      
      TV.set_cursor(cursorX, cursorY);
      TV.print(keyChar);

      cursorX += 6;

      // Handle screen wrap
      if (cursorX > 120) {
        cursorX = 0;
        cursorY += 8;
      }

      // Handle screen clear when reaching bottom
      if (cursorY > 88) {
        TV.clear_screen();
        // Redraw Header
        TV.print(0, 0, "TV TYPEWRITER");
        TV.print(0, 10, "RONI BANDINI 3/26");
        TV.print(0, 20, "-----------------");
        cursorX = 0;
        cursorY = 32; 
      }
      
      delay(250); // Debounce
    }
  }
}

void ADKeybegin() {
  // Resistor values for DFRobot ADKeypad
  float RESValue[10] = {0, 3, 6.2, 9.1, 15, 24, 33, 51, 100, 220};
  for (uint8_t i = 0; i < 10; i++) {
    ADKeyVal[i] = (RESValue[i] / (RESValue[i] + 22)) * MAXVALUE;
  }
}

int8_t getKey() {
  for (uint8_t i = 0; i < 10; i++) {
    int32_t diff = (int32_t)ADCKeyIn - (int32_t)ADKeyVal[i];
    if (abs(diff) < PRECISION) {
      return i;
    }
  }
  return -1;
}