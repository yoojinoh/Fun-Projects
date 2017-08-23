#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 25
#define BRIGHTNESS 80
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

int red = 0;
int green = 0;
int blue = 0;
bool enable;
int nowhour;

void setup() {
  Serial.begin(9600);
   strip.setBrightness(BRIGHTNESS);
  strip.begin();
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
    rainbow(10);
  }
 
  strip.show(); // Initialize all pixels to 'off'

  pinMode(5, OUTPUT);
  enable = true;
}

void loop() {
  DateTime now = RTC.now();
  red = map(analogRead(A0), 0, 1023, 255, 0);
  green = map(analogRead(A1), 0, 1023, 255, 0);
  blue = map(analogRead(A2), 0, 1023, 255, 0);

  if (now.minute() % 5 == 0 && now.second() % 10 < 3 )
  {
    enable = true;
  }
  if (enable == true) {
    initializePixels();
    nowhour = now.hour();
    if ((now.minute() + 5) % 10 >=5)
    {
      strip.setPixelColor(23, red, green, blue, 0);
      strip.setPixelColor(24, red, green, blue, 0);
    }
    switch ((now.minute() + 5) / 10) {
      case 1:
        strip.setPixelColor(22, red, green, blue, 0);
        strip.setPixelColor(24, red, green, blue, 0);
        break;
      case 2:
        strip.setPixelColor(17, red, green, blue, 0);
        strip.setPixelColor(22, red, green, blue, 0);
        strip.setPixelColor(24, red, green, blue, 0);
        break;
      case 3:
        strip.setPixelColor(16, red, green, blue, 0);
        strip.setPixelColor(15, red, green, blue, 0);
        strip.setPixelColor(24, red, green, blue, 0);
        break;
      case 4:
        strip.setPixelColor(20, red, green, blue, 0);
        strip.setPixelColor(22, red, green, blue, 0);
        strip.setPixelColor(24, red, green, blue, 0);
        break;
      case 5:
        strip.setPixelColor(21, red, green, blue, 0);
        strip.setPixelColor(22, red, green, blue, 0);
        strip.setPixelColor(24, red, green, blue, 0);
        break;
      case 6:
        nowhour = now.hour() + 1;
        break;
      default:
        break;
    }
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;

    switch (nowhour) {
      case 0:
        strip.setPixelColor(19, red, green, blue, 0);
        strip.setPixelColor(18, red, green, blue, 0);
        break;
      case 12:
        strip.setPixelColor(18, red, green, blue, 0);
        strip.setPixelColor(21, red, green, blue, 0);
      case 1:
      case 13:
        strip.setPixelColor(1, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 2:
      case 14:
        strip.setPixelColor(9, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 3:
      case 15:
        strip.setPixelColor(3, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 4:
      case 16:
        strip.setPixelColor(4, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 5:
      case 17:
        strip.setPixelColor(2, red, green, blue, 0);
        strip.setPixelColor(7, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 6:
      case 18:
        strip.setPixelColor(8, red, green, blue, 0);
        strip.setPixelColor(7, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 7:
      case 19:
        strip.setPixelColor(5, red, green, blue, 0);
        strip.setPixelColor(6, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 8:
      case 20:
        strip.setPixelColor(10, red, green, blue, 0);
        strip.setPixelColor(11, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 9:
      case 21:
        strip.setPixelColor(12, red, green, blue, 0);
        strip.setPixelColor(13, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 10:
      case 22:
        strip.setPixelColor(0, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
      case 11:
      case 23:
        strip.setPixelColor(0, red, green, blue, 0);
        strip.setPixelColor(1, red, green, blue, 0);
        strip.setPixelColor(14, red, green, blue, 0);
        break;
        default:
        break;
    }
    strip.show();
    enable = false;
    delay(4000);
  }
}

void initializePixels() {
  for (int i = 0; i < 25; i++)
  {
    strip.setPixelColor(i, 0, 0, 0, 0);
  }
  strip.show();
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0, 0);
}
