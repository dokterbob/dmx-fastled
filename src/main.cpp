#include <FastLED.h>
#include <Candle.h>

#define ONBOARD_LED 2

#define NUM_LEDS 9

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
        candles[i].init(96, 255, 2, 96);

        // Initialize random saturation
        saturation[i].init(112, 255, 20, 62);

    }
}


uint8_t hue = 0;
void loop()
{
    digitalWrite(ONBOARD_LED,HIGH);

    EVERY_N_MILLIS(16) {
      for (size_t i=0; i<NUM_LEDS; i++) {
          leds[i] = CHSV(
            add8(hue, mul8(i, 120)),
            saturation[i].get_next_brightness(),
            candles[i].get_next_brightness()
          );
      }
    }

    FastLED.show();

    EVERY_N_MILLIS(150) {
      hue++;
    }
}
