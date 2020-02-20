#include <Arduino.h>
#include "SPI.h"
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

#include "src/MusicalFloppyDrives.h"
#include "src/Adafruit_WS2801.h"

#define NUMBER_OF_LEDS 20
#define RAINBOW_DELAY_MS 15
#define ONE_BYTE_SHIFT 8
#define COLOR_WHEEL_THRESHOLD_1 85
#define COLOR_WHEEL_THRESHOLD_2 170
#define MIN_RGB_VALUE 0
#define MAX_RGB_VALUE 255
#define RGB_COMPONENTS_NUMBER 3
#define ITERATOR_INITIAL_VALUE 0

// LED strip functions prototypes
uint32_t createColorRGB(byte r, byte g, byte b);
uint32_t createColorWheel(byte initialWheelPos);
void showRainbow(byte delayMS);

// Instances of objects
MusicalFloppyDrives floppyMusicalDrives = MusicalFloppyDrives();
Adafruit_WS2801 ledStrip = Adafruit_WS2801(NUMBER_OF_LEDS);

// Setup --> called once, at startup
void setup()
{
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  // Initialize LED strip and floppy drives
  ledStrip.begin();
  ledStrip.show();
  floppyMusicalDrives.setup();

  // Play hardcoded song just once
  floppyMusicalDrives.playImperialMarchSong();
}

// Loop --> called infinitely
void loop()
{
  showRainbow(RAINBOW_DELAY_MS);
}

// Function definitions of above prototypes

// Create a color given the three R, G and B components between 0 and 255
uint32_t createColorRGB(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= ONE_BYTE_SHIFT;
  c |= g;
  c <<= ONE_BYTE_SHIFT;
  c |= b;
  return c;
}

// Move through all colors given an starting color between 0 and 255
uint32_t createColorWheel(byte initialColor)
{
  if (initialColor < COLOR_WHEEL_THRESHOLD_1)
    return createColorRGB(initialColor * RGB_COMPONENTS_NUMBER, MAX_RGB_VALUE - initialColor * RGB_COMPONENTS_NUMBER, MIN_RGB_VALUE);
  else if (initialColor < COLOR_WHEEL_THRESHOLD_2)
  {
    initialColor -= COLOR_WHEEL_THRESHOLD_1;
    return createColorRGB(MAX_RGB_VALUE - initialColor * RGB_COMPONENTS_NUMBER, MIN_RGB_VALUE, initialColor * RGB_COMPONENTS_NUMBER);
  }
  else
  {
    initialColor -= COLOR_WHEEL_THRESHOLD_2; 
    return createColorRGB(MIN_RGB_VALUE, initialColor * RGB_COMPONENTS_NUMBER, MAX_RGB_VALUE - initialColor * RGB_COMPONENTS_NUMBER);
  }
}

// Show a rainbow which color moves with a given delay
void showRainbow(byte movingDelayMS)
{
  int iterator_1, iterator_2;
  for (iterator_2 = ITERATOR_INITIAL_VALUE; iterator_2 <= MAX_RGB_VALUE; iterator_2++)
  {
    for (iterator_1 = ITERATOR_INITIAL_VALUE; iterator_1 < ledStrip.numPixels(); iterator_1++)
      ledStrip.setPixelColor(iterator_1, createColorWheel( (iterator_1 + iterator_2) % MAX_RGB_VALUE));
    ledStrip.show();
    delay(movingDelayMS);
  }
}