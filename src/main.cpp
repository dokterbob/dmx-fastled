#include <FastLED.h>

#define ONBOARD_LED 2

#define NUM_LEDS    3

CRGB leds[NUM_LEDS];

void setup() {
    delay( 3000 ); // power-up safety delay

    pinMode(ONBOARD_LED, OUTPUT);

    FastLED.addLeds<ESPDMX>(leds, NUM_LEDS);
    FastLED.setCorrection(Typical8mmPixel);
    FastLED.setTemperature(Candle);
}


uint8_t hue = 0;
void loop()
{
    digitalWrite(ONBOARD_LED,HIGH);

    fill_rainbow(leds, NUM_LEDS, hue, 360/NUM_LEDS);

    FastLED.show();
    FastLED.delay(100);

    hue++;
}




// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
