const int LIGHTNESS_MAX = 4096;

struct Led
{
    static void setup();

    int mLightness = 0;
    const int mPin;
    int mDelta = 4;

    Led(int pin) : mPin(pin) {}

    void update();
};