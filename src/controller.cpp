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

void controllerLoop()
{
    for (int i = 8; i < 15; i++)
    {
        bool state = mcp.digitalRead(i);
        if (pinState[i] != state)
        {
            Serial.print("PIN ");
            Serial.print(i);
            Serial.println(state ? " 1" : " 0");
            pinState[i] = state;
        }
    }
}

void Controller::update()
{
    mLastIsPressed = mIsPressed;
    mIsPressed = !mcp.digitalRead(mKeyPin);
    if (mIsPressed != mLastIsPressed) {
        Serial.printf("pRESSED: %d\n", mIsPressed);

    }

    bool s1 = mcp.digitalRead(mS1Pin);
    bool s2 = mcp.digitalRead(mS2Pin);
    if (s2 == 0 && mLastS2 == 1)
    {
        mValue += (s1 == s2) ? 1 : -1;
    }
    // if (s1 != mLastS1 || s2 != mLastS2) {
    //     Serial.printf("Value: %d, s1: %d, s2: %d\n", mValue, s1, s2);
    // }
    mLastS1 = s1;
    mLastS2 = s2;
}