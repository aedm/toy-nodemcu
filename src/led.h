const int CHANNEL_LIGHTNESS_MAX = 4096;

const int LED_HUE_WIDTH = 4096;
const int LED_LIGHTNESS_WIDTH = 4096;

void setupLed();

struct LedChannel
{
    int mLightness = CHANNEL_LIGHTNESS_MAX;
    int mPin;
 
    LedChannel(int pin = 0) : mPin(pin) {}
    void update();
};

struct Led {
    int mHue = 0;
    int mLightness = LED_LIGHTNESS_WIDTH;

    Led(int redPin, int greenPin, int bluePin): mRed(redPin), mGreen(greenPin), mBlue(bluePin) {}
    void update();

    // private:
        LedChannel mRed;
        LedChannel mGreen;
        LedChannel mBlue;
};
