
#include <OctoWS2811.h>

const int ledsPerStrip = 100;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_RGB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

#define BLACK 0x000000
#define BLUE   0x2222FF

int inputNumber;

void setup() {
  leds.begin();
  leds.show();

  inputNumber = 0;

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Indexing tool.");
  Serial.println("Input a number followed by a space.");
  Serial.println("> ");
}

void loop() {
  handleSerial();
}

void handleSerial() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    int i = c - '0';
    if (i >= 0 && i < 10) {
      inputNumber = inputNumber * 10;
      inputNumber += i;
    } else {
      Serial.print("> ");
      Serial.println(inputNumber);

      displayIndex(inputNumber);
      inputNumber = 0;
    }
  }
}

void displayIndex(int index) {
  for (int i = 0; i < leds.numPixels(); i++) {
    if (i == index) {
      leds.setPixel(i, BLUE);
    } else {
      leds.setPixel(i, BLACK);
    }
  }
  leds.show();
}

void colorWipe(int color) {
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
  }
}
