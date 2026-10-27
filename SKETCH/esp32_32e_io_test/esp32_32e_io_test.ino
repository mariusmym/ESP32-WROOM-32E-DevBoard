#include <Adafruit_NeoPixel.h>

#define USER_LED 2
#define RGB_PIN  18
#define BTN_PIN  0   // BOOT button, active LOW

Adafruit_NeoPixel rgb(1, RGB_PIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[4];
uint8_t  idx = 0;            // 0-3 = fixed colors, 4 = rainbow
const uint8_t MODES = 5;
uint16_t hue = 0;

void showColor() {
  if (idx < 4) {
    rgb.setPixelColor(0, colors[idx]);
  } else {
    rgb.setPixelColor(0, rgb.gamma32(rgb.ColorHSV(hue)));
  }
  rgb.show();
}

void setup() {
  pinMode(USER_LED, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  rgb.begin();
  rgb.setBrightness(40); // it's a 2020 LED, not a stadium floodlight

  colors[0] = rgb.Color(255, 0, 0);
  colors[1] = rgb.Color(0, 255, 0);
  colors[2] = rgb.Color(0, 0, 255);
  colors[3] = rgb.Color(255, 255, 255);

  showColor();
}

void loop() {
  static bool lastState = HIGH;
  bool state = digitalRead(BTN_PIN);

  if (state == LOW && lastState == HIGH) {   // button just pressed
    idx = (idx + 1) % MODES;
    digitalWrite(USER_LED, !digitalRead(USER_LED));
    showColor();
  }
  lastState = state;

  if (idx == 4) {                            // rainbow mode
    hue += 256;                              // full wheel in ~5s
    showColor();
  }

  delay(20); // simple debounce + rainbow step
}
