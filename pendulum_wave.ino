#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.

// On an ESP8266 NodeMCU :  D2(SDA), D1(SCK)

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin, or using nodeMCU)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  drawPendulums();
}
void loop() {

}

void drawPendulums() {
  float x = 0;
  const int numCircles = 16;
  const int circleSize = 6;
  const int gap = 2;
  const int dist = circleSize + gap;
  const int A = display.height() / 2 - circleSize;


  for (;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each pendulum:
    for (int i = 0 ; i < numCircles; i++) {
      float f = (60 + i) / 60.0;
      display.fillCircle(
        dist / 2 + dist * i,
        A * sin(2.0 * PI * f * x) + display.height() / 2,
        circleSize / 2,
        SSD1306_WHITE);
    }
    display.display();
    x += 0.01;
    Serial.println(x);
    delay(10);

  }
}
