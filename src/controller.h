
void setupController();
void controllerLoop();

struct Controller
{
    int mValue = 0;
    bool mIsPressed = false;
    bool mLastIsPressed = false;

    Controller(int s1Pin, int s2Pin, int keyPin) : mS1Pin(s1Pin), mS2Pin(s2Pin), mKeyPin(keyPin) {}
    void update();

private:
    int mS1Pin, mS2Pin, mKeyPin;
    bool mLastS1 = false;
    bool mLastS2 = false;
};
