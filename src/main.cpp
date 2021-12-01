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

Controller knobs[] = {
    Controller(5, 6, 7),
    Controller(2, 3, 4),
    Controller(10, 9, 8),
    Controller(13, 12, 11),
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

int led5 = 0;
bool isColorLoop = false;
int colorLoopValue = 0;

void loop()
{
  int currentTime = micros();
  int elapsedTime = currentTime - lastLoopMicros;
  if (elapsedTime < LOOP_EVERY_MICROS)
  {
    return;
  }
  lastLoopMicros += LOOP_EVERY_MICROS;
  // showFPS(currentTime);

  if (knobs[3].mIsPressed && !knobs[3].mLastIsPressed)
  {
    isColorLoop = !isColorLoop;
    if (!isColorLoop)
    {
      colorLoopValue = 0;
    }
  }
  if (isColorLoop)
  {
    colorLoopValue += 150;
  }

  if (knobs[1].mIsPressed && !knobs[1].mLastIsPressed)
  {
    int index = rand() % 5;
    int value = rand() % 1000;
    if (index < 4)
    {
      knobs[index].mValue = value;
    }
    else
    {
      led5 = value;
    }
  }

  if (knobs[2].mIsPressed && !knobs[2].mLastIsPressed)
  {
    for (int i = 0; i < 4; i++)
    {
      knobs[i].mValue = rand() % 1000;
    }
    led5 = rand() % 1000;
  }

  for (int i = 0; i < 4; i++)
  {
    knobs[i].update();
    leds[i].mHue = knobs[i].mValue * LED_HUE_WIDTH + colorLoopValue;
    leds[i].update();
  }

  if (knobs[0].mIsPressed && !knobs[0].mLastIsPressed)
  {
    led5++;
  }

  leds[4].mHue = led5 * LED_HUE_WIDTH + colorLoopValue;
  leds[4].update();

  // for (int i = 1; i < 5; i++)
  // {
  //   leds[i].mHue += 200;
  //   leds[i].update();
  // }

  // Serial.printf("LED1: %d %d %d\n", leds[0].mRed.mLightness, leds[0].mGreen.mLightness, leds[0].mBlue.mLightness);

  // controllerLoop();

  // delayMicroseconds(DELAY_MICRO);
}