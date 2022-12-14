#pragma once

#ifndef DRIVE_H_
#define DRIVE_H_

#include <Arduino.h>
#include <Servo.h>
#include <PolarRobotics.h>
// #include <Servo_Hardware_PWM.h>

#ifndef NUM_MOTORS
// the number of motors associated with driving, usually multiples of 2, default: 2
#define NUM_MOTORS 2 // 4 for mechanum wheels
#endif

// #TODO move this to the robot parent class
// #ifndef MECHANUM
// // determine if the motors are in a mechanum configuration or the standard config. default: false
// #define MECHANUM false
// #endif

// rate of change of power with respect to time when accelerating %power/10th of sec
#define ACCELERATION_RATE .0375
// rate of deceleration/braking
#define BRAKE_PERCENTAGE 0.9
// how often the ramp() function changes the motor power
#define TIME_INCREMENT 25
#define BREAK_TIME_INCREMENT 12.5
// DO NOT CHANGE THIS EVER!!!!!
#define PWM_CONVERSION_FACTOR 0.3543307087

#define NORMAL_TURN_CONSTANT 0.05

// Controller Defines
#define OFFSET -0.15 // the max allowable turning when the bot is traveling at full speed
#define STICK_DEADZONE 0.0390625F // 8.0 / 127.0
#define THRESHOLD 0.00001

// this is 1.0, the maximum power possible to the motors.
#define BIG_BOOST_PCT 0.9  // default: 0.6, this is the typical percentage of power out of the motors' range that is used (to ensure they don't do seven wheelies)
#define BIG_NORMAL_PCT 0.5 // should be a value less than BIG_NORMAL_PCT, to slow down for precision maneuvering
#define BIG_SLOW_PCT 0.2   // the value for brake button to slow down the motors at the button press
#define BRAKE_BUTTON_PCT 0

// BSN for Short/Small Motors
#define SMALL_BOOST_PCT 0.55
#define SMALL_NORMAL_PCT 0.55
#define SMALL_SLOW_PCT 0.3

// Value for the tank mode speed reduction percentage
#define TANK_MODE_PCT 0.75
// Value for the Drift Mode Reduction Factor Percentage
#define DRIFT_MODE_PCT 0.8

class Drive {
private:
  float stickForwardRev, stickTurn;
  float BSNscalar;
  float lastTurnPwr;
  float turnPower;

  Servo M1, M2; //temporary solution, use vector for future
  MOTORS motorType;
  // vector<Servo> Motors;
  // motor variables
  uint8_t motorPins[NUM_MOTORS];
  unsigned long lastRampTime[NUM_MOTORS];
  float motorPower[NUM_MOTORS];
  float currentPower[NUM_MOTORS];
  float lastRampPower[NUM_MOTORS];
  // float inputPower[NUM_MOTORS];
  // float rampedPower[NUM_MOTORS];
  float calcTurningMotorValue(float stickTrn,  float prevPwr);
  void generateMotionValues();
  float ramp(float requestedPower, uint8_t mtr);
  // use the inline keywork to ensure the function will get called again as soon as possible
  uint32_t Convert2PWM(float rampPwr);
  void setMotorPWM(float pwr, byte pin); //__attribute__((always_inline));

public:
  enum SPEED {
    normal,
    boost,
    slow,
    brake
  };
  Drive();
  void setServos(Servo&, Servo&);
  void setMotorType(MOTORS motorType);
  void attach();
  void setStickPwr(int8_t leftY, int8_t rightX);
  void setBSN(SPEED bsn); //(float powerMultiplier);
  float getMotorPwr(uint8_t mtr);
  void emergencyStop();
  void update();
  void drift();
  void printDebugInfo();
};

// // Robot Age Enum
// // 0 for old robot, 1 for new robot
// // remove later - deprecated
// enum AGE {
//   OLD,
//   NEW
// };

#endif /* DRIVE_H */
