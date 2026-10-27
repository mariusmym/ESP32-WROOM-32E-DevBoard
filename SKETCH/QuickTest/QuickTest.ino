// ESP32-WROOM-32E DevBoard - quick test
// Blinks the user LED on IO2, cycles the WS2812B RGB LED on IO18 and prints to Serial.
// NOTE: close solder bridge SB1 first, otherwise the RGB LED isn't connected to IO18.

#include <Adafruit_NeoPixel.h>

#define USER_LED 2
#define RGB_PIN  18

Adafruit_NeoPixel rgb(1, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pinMode(USER_LED, OUTPUT);
  rgb.begin();
  rgb.setBrightness(40);  // it's a 2020 LED, not a stadium floodlight
  Serial.println("Hello from the ESP32-WROOM-32E DevBoard!");
}

void loop() {
  const uint32_t colors[] = { rgb.Color(255, 0, 0), rgb.Color(0, 255, 0), rgb.Color(0, 0, 255) };
  const char* names[] = { "red", "green", "blue" };
  for (uint8_t i = 0; i < 3; i++) {
    digitalWrite(USER_LED, !digitalRead(USER_LED));
    rgb.setPixelColor(0, colors[i]);
    rgb.show();
    Serial.println(names[i]);
    delay(500);
  }
}
