#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"

#define AL_ADDR 0x48
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

SparkFun_Ambient_Light light(AL_ADDR);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float gain = 0.125;
int time = 100;
long luxVal = 0;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  if (light.begin())
    Serial.println("Ready to sense some light!");
  else
    Serial.println("Could not communicate with the sensor!");

  light.setGain(gain);
  light.setIntegTime(time);

  Serial.println("Reading settings...");
  Serial.print("Gain: ");
  float gainVal = light.readGain();
  Serial.print(gainVal, 3);
  Serial.print(" Integration Time: ");
  int timeVal = light.readIntegTime();
  Serial.println(timeVal);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  luxVal = light.readLight();
  Serial.print("Ambient Light Reading: ");
  Serial.print(luxVal);
  Serial.println(" Lux");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Lux: ");
  display.println(luxVal);
  display.display();

  delay(1000);
}
