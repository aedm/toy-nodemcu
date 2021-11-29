#include "led.h"
#include "controller.h"
#include <Arduino.h>

unsigned long lastLoopMicros;
int frameCount = 0;
unsigned long lastFrameDump = 0;

const int DELAY_MICRO = 5000;
const int LOOP_EVERY_MICROS = 10000;

Led leds[] = {
    Led(0, 1, 2),
    Led(3, 4, 5),
    Led(6, 7, 8),
    Led(9, 10, 11),
    Led(12, 13, 14),
};

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Starting.");

  setupController();
  setupLed();

  for (int i = 0; i < 5; i++)
  {
    leds[i].mHue = LED_HUE_WIDTH * i;
  }

  Serial.println("Looping...");
  lastLoopMicros = micros();
  lastFrameDump = lastLoopMicros;
}

void showFPS(int currentTime)
{
  frameCount++;
  if (currentTime - lastFrameDump > 1000 * 1000)
  {
    lastFrameDump = currentTime;
    Serial.printf("FPS: %d\n", frameCount);
    frameCount = 0;
  }
}

void loop()
{
  int currentTime = micros();
  int elapsedTime = currentTime - lastLoopMicros;
  if (elapsedTime < LOOP_EVERY_MICROS)
  {
    return;
  }
  lastLoopMicros += LOOP_EVERY_MICROS;
  showFPS(currentTime);

  for (int i = 0; i < 5; i++)
  {
    leds[i].mHue += 200;
    leds[i].update();
  }

  // Serial.printf("LED1: %d %d %d\n", leds[0].mRed.mLightness, leds[0].mGreen.mLightness, leds[0].mBlue.mLightness);

  

  controllerLoop();

  // delayMicroseconds(DELAY_MICRO);
}