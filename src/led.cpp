#include <Adafruit_PWMServoDriver.h>
#include "led.h"

Adafruit_PWMServoDriver pwm;

#define SERVOMIN 150    // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600    // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 600       // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2400      // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 1600 // Analog servos run at ~50 Hz updates

void setupLed()
{
    Wire.begin();
    pwm.begin();
    /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates

    delay(100);

    for (int i = 0; i < 16; i++)
    {
        pwm.setPWM(i, 0, 2048);
    }
}

void LedChannel::update()
{
    pwm.setPWM(mPin, 0, mLightness < CHANNEL_LIGHTNESS_MAX ? mLightness : (CHANNEL_LIGHTNESS_MAX - 1));
}

int mgx(int x)
{
    int h6 = 6 * LED_HUE_WIDTH;
    int v = x % h6;
    if (v < 0) { v+= h6;}
    if (v > h6 / 2) { v -= h6; }
    return v < 0 ? -v : v;
}

int mg2x(int x)
{
    int v = (2 * LED_HUE_WIDTH - mgx(x)) * CHANNEL_LIGHTNESS_MAX / LED_HUE_WIDTH;
    if (v > CHANNEL_LIGHTNESS_MAX)
    {
        v = CHANNEL_LIGHTNESS_MAX;
    }
    else if (v < 0)
    {
        v = 0;
    }
    return v;
}

void Led::update()
{
    mRed.mLightness = mg2x(mHue);
    mGreen.mLightness = mg2x(mHue - 2 *LED_HUE_WIDTH);
    mBlue.mLightness = mg2x(mHue - 4 *LED_HUE_WIDTH);

    mRed.update();
    mGreen.update();
    mBlue.update();

    // Serial.printf("HUE: %d, RGB: %d, %d, %d\n", mHue, mRed.mLightness, mGreen.mLightness, mBlue.mLightness);
}