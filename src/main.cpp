#include <FastLED.h>
#include <Candle.h>

#define ONBOARD_LED 2

#define NUM_LEDS    3

CRGB leds[NUM_LEDS];
candle::Candle candles[NUM_LEDS];
candle::Candle saturation[NUM_LEDS];

void setup() {
    delay( 3000 ); // power-up safety delay

    pinMode(ONBOARD_LED, OUTPUT);

    FastLED.addLeds<ESPDMX>(leds, NUM_LEDS);
    FastLED.setCorrection(TypicalPixelString);
    FastLED.setTemperature(Candle);
    // FastLED.setBrightness(8); // THIS WORKS SO FUCKING WELL!!!

    for (size_t i=0; i<NUM_LEDS; i++) {
        // Reset LED values
        leds[i] = CRGB::Black;

        // Initialize candles
        candles[i].init(random8(16, 96), 255, random8(3, 8), random8(6, 22));

        // Initialize random saturation
        saturation[i].init(random8(112, 240), random8(241, 255), random8(10, 20), random8(22, 62));

    }
}


uint8_t hue = 0;
void loop()
{
    digitalWrite(ONBOARD_LED,HIGH);

    EVERY_N_MILLIS(20) {
      for (size_t i=0; i<NUM_LEDS; i++) {
          leds[i] = CHSV(hue + i*120, saturation[i].get_next_brightness(), candles[i].get_next_brightness());
      }
    }

    fill_rainbow(leds, NUM_LEDS, hue, 360/NUM_LEDS);

    FastLED.show();

    EVERY_N_MILLIS(150) {
      hue++;
    }
}
