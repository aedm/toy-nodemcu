#include "led.h"
#include <Adafruit_MCP23X17.h>

// uncomment appropriate line
Adafruit_MCP23X17 mcp;
TwoWire Wire2;

unsigned long lastLoopMicros;

const int DELAY_MICRO = 1;
const int LOOP_EVERY_MICROS = 10;

Led red(0);
Led green(1);
Led blue(2);

bool pinState[16];

void setupMCP() {
  Wire2.begin(2, 0);
  Wire2.setClock(400000);

  if (!mcp.begin_I2C(0x20, &Wire2)) {
    Serial.println("Error!");
    while (1);
  }

  for (int i=8; i<15; i++) {
    mcp.pinMode(i, INPUT);
    pinState[i] = false;
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Starting.");

  // setupMCP();
  Led::setup();

  green.mLightness = LIGHTNESS_MAX * 2 / 3;
  blue.mLightness = LIGHTNESS_MAX * 2 / 3;
  blue.mDelta *= -1;

  Serial.println("Looping...");
  lastLoopMicros = micros();
}

void loop() {
  // int currentTime = micros();
  // int elapsedTime = currentTime - lastLoopMicros;
  // if (elapsedTime < LOOP_EVERY_MICROS) {
  //   // Serial.print("low pass");
  //   // Serial.println(elapsedTime);
  //   // return;
  // }
  // lastLoopMicros += LOOP_EVERY_MICROS;

  red.update();
  green.update();
  blue.update();

  // for (int i=8; i<15; i++) {
  //   bool state = mcp.digitalRead(i);
  //   if (pinState[i] != state) {
  //     Serial.print("PIN ");
  //     Serial.print(i);
  //     Serial.println(state ? " 1" : " 0");
  //     pinState[i] = state;
  //   }
  // }


  // delayMicroseconds(DELAY_MICRO);
  // Serial.print("getLastInterruptPin");
  // Serial.println(mcp.getLastInterruptPin());
}