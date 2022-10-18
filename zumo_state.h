/*
 * Zumo Demo
 *
 * Based on Polulu line-following example
 */

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

#define condition true
#define port 1

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
#define NUM_SENSORS 6
unsigned int sensorValues[NUM_SENSORS];

int lastError = 0;

unsigned int sensors[6];

int position=0;
