// void updateLEDS(BOT_STATE status); //private
// void setRobotState(BOT_STATE state);

#include <FastLED.h>
#define LED_PIN 7
#define NUM_LEDS 30
#define TIME_BETWEEN_TOGGLES 25

class Lights {
private:
    unsigned long lastToggleTime;
    uint8_t currState; // LEDState currState;
    CRGBArray<NUM_LEDS> leds;
    uint8_t iteration;
    bool m_isOffense;
    // int i, updateCount;
public:
    // MUHAMMED ENUM PRAISE BE UPON HIM
    enum LEDState {
        PAIRING,     // Yellow
        PAIRED,      // green then fade out
        OFFENSE,     // blue (also need green)
        DEFENSE,     // green
        BALL_CARRIER // turn red and then go back to offense state (testing digital pin signal)
    };
    Lights();
    void setupLEDS();
    void setLEDStatus(LEDState status);
    // void setLEDColor(uint8_t r, uint8_t g, )
    void updateLEDS();
    //   void runLoop(int count);
    void togglePosition();
};

// Function Definitions

Lights::Lights() {
    currState = PAIRING;
    m_isOffense = false;
}

void Lights::setupLEDS() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); // Power Failsafe
    // Clears LEDs when code is updated
    FastLED.clear();

    updateLEDS();
    FastLED.setBrightness(110);
}

// To set LED status
void Lights::setLEDStatus(LEDState status) {
    currState = status;
    updateLEDS();
}

// To change LED color
void Lights::updateLEDS() {
    switch (currState) {
    case PAIRING: {
        leds = CRGB::Yellow;
        break;
    }
    case PAIRED: {
        leds = CRGB::Green;
        FastLED.setBrightness(iteration);
        iteration++;
        break;
    }
    case OFFENSE: {
        leds = CRGB::Blue;
        break;
    }
    case DEFENSE: {
        leds = CRGB::Green;
        break;
    }
    case BALL_CARRIER: {
        if (iteration % 255 / 16 == 0) {
            leds = CRGB::Red;
            // FastLED.delay(30);
        }
        else {
            leds = CRGB::Black;
        }
        iteration++;
        break;
    }
    default: {
        leds = CRGB::Red;
        break;
    }
    }
    FastLED.show();
}

void Lights::togglePosition() {
    // debounce makes sure you cant hold down the button, 
    // i think the ps5 library already does this we probably should check
    if (millis() - lastToggleTime >= TIME_BETWEEN_TOGGLES) {
        if (m_isOffense) {
            setLEDStatus(DEFENSE);
        }
        else {
            setLEDStatus(OFFENSE);
        }
        m_isOffense = !m_isOffense;
        lastToggleTime = millis();
    }
}
