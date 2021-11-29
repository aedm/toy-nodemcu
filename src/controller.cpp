#include "controller.h"

#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;
TwoWire Wire2;

bool pinState[16];

void setupController()
{
    // Wire2.begin(D4, D3);
    // Wire2.setClock(400000);

    // if (!mcp.begin_I2C(0x20, &Wire2))
    if (!mcp.begin_I2C(0x20))
    {
        Serial.println("Error!");
        while (1)
            ;
    }

    for (int i = 0; i < 15; i++)
    {
        mcp.pinMode(i, INPUT);
        pinState[i] = false;
    }
}

void controllerLoop() {
  for (int i=8; i<15; i++) {
    bool state = mcp.digitalRead(i);
    if (pinState[i] != state) {
      Serial.print("PIN ");
      Serial.print(i);
      Serial.println(state ? " 1" : " 0");
      pinState[i] = state;
    }
  }
}