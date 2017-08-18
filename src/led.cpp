#include <Arduino.h>
#include "led.h"
#include "configure.h"

#include <Adafruit_NeoPixel.h>

extern void setRingColor(uint8_t ring, uint8_t r, uint8_t g, uint8_t b, uint8_t w);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LEDPIN, NEO_GRBW + NEO_KHZ800);

void led_setup(void)
{
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  setRingColor(0, 255, 0, 0, 0);
  setRingColor(1, 0, 255, 0, 0);
  setRingColor(2, 0, 0 , 255, 0);

}



// void meetingIndicator(uint8_t) {
//
//   for(i=0; i<strip.numPixels(); i++) {
//
//   for(i=0; i<strip.numPixels(); i++) {
//
// }

void setRingColor(uint8_t ring, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  if (ring < RING_NUM) {
    for (uint8_t i = (ring * NUM_LEDS_RING); i < ((ring + 1) * NUM_LEDS_RING); i++) {
      strip.setPixelColor(i, r, g, b, w);
    }
    strip.show();
  }

  /*
  solid color timing egal
  rainbow timer wichtig
  blinking time wichtig
  fade time wichtig  
  */
}
