#include <math.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    6
#define LED_COUNT 8

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

}

void loop() 
{

  //pinkBreath(strip.Color(255, 0, 127), 3000);
  theaterChasePink(50);
}

void pinkBreath(uint32_t color, uint16_t duration)
{
  uint16_t steps = 30;  // Number of steps in uthe breathing effect
  uint16_t delayTime = duration / (2 * steps);
  //static float phase = 4.0;  // Start phase at 0


 for (uint16_t i = 0; i <= steps; i++) {
    uint8_t brightness = 128 + 127 * sin((i * PI) / steps);  // Sine function for smooth fading

    strip.fill(strip.Color((brightness * 255) / 255, 
                           (brightness * 0) / 255, 
                           (brightness * 127) / 255));

    strip.show();
    delay(delayTime);
  }
}

// Function for theater chase effect with pink color and changing brightness
void theaterChasePink(uint16_t delayTime) {
  for (int j = 0; j < 10; j++) {  // Run the chase effect for 10 cycles
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        uint8_t brightness = 128 + 127 * sin((i + q + j) * 2 * PI / strip.numPixels());

       // strip.setPixelColor(i + q, strip.ColorHSV(330, 255, brightness));  // 330 is the hue for pink


        strip.setPixelColor(i + q, strip.Color((brightness * 255) / 255, 
                                               (brightness * 0) / 255, 
                                               (brightness * 127) / 255));

      }
      strip.show();
      delay(delayTime);
    }
  }
  delay(delayTime);  // Pause before starting the next cycle
}

