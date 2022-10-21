#include "zumo_state.h"

// setup a set of states here for the zumo to follow

/* -------- SET MOTOR VALUES---------- */

// These define statements allow us to set some useful values for later
// This type of construction is often used to make a system clearer to
// understand

// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)

#define SPEED_MAX 200
#define SPEED_HALT 0

/* -----------STATE ENCODING---------- */

// These defines define the state encoding - a mapping from a name to a numerical code
// Add new state definitions by copying the lines here and incrementing the number by one.
// Note: make sure each encoding is unique

#define STATE_FORWARD 0
#define STATE_LEFT    1
#define STATE_RIGHT   2
#define STATE_ALLWHITE 4
#define STATE_ALLBLACK  5

/* ---------END STATE ENCODING---------- */

// Create a variable to hold a state.  This should be set to the default state.
int state = STATE_FORWARD;

// Create a variable to hold the next state.  This should also be set to the default state.
int next_state = STATE_FORWARD;

/* -----------STATE IMPLEMENTATION---------- */

// Each state should be implemented by a function.
// Each function should also report its state to the wireless serial

// Serial  - usb connected serial interface
// Serial0 - wireless connected serial interface

// Each state implements a set of actions.  In this case, we can set the motor
// speeds.

void stateForward()
{
  Serial.println("forward");
  Serial0.println("forward");
  motors.setSpeeds(SPEED_MAX, SPEED_MAX);
}

void stateLeft()
{
  Serial.println("left");
  Serial0.println("left");
  motors.setSpeeds(SPEED_HALT, SPEED_MAX);  
}

void stateRight()
{
  Serial.println("right");
  Serial0.println("right");
  motors.setSpeeds(SPEED_MAX, SPEED_HALT);  
}

void stateallwhite()
{
  Serial.println("ALLWHITE");
  Serial0.println("ALLWHITE");
  motors.setSpeeds(SPEED_MAX, SPEED_MAX);
  delay(1000);
  motors.setSpeeds(SPEED_HALT, SPEED_HALT);  
}

void stateallblack()
{
  Serial.println("halt");
  Serial0.println("halt");
  motors.setSpeeds(SPEED_HALT, SPEED_HALT);  
}

int randomgen()
{
  int randnum = random(2);
  Serial.println(randnum);
  if(randnum == 1) 
  {
    Serial.println("Head");
  } else 
  {
    Serial.println("Tail");
  }
  return randnum;
}

/* -------END STATE IMPLEMENTATION---------- */

/* -----------STATE CHOICE---------- */

void selectState()
{

  // Update the position estimate and sensor value
  // position is an estimate of the relative position of the line
  // The value runs in the range of 0-5000.
  //
 
  position = reflectanceSensors.readLine(sensors);
  Serial.println(position);
 

  // Choose the next state that the vehicle will be in.
  // Put your state selection logic here

  // Each state needs an if statement like this.  It will
  // be true when the state matches our encoded state
 if(position > 2000 && position <3000) // Put your condition here
    {
      // Write your desired state here
      next_state = STATE_FORWARD;
    }
    
  if(state == STATE_FORWARD)
  {
    // You choose the state to transition to by writing a
    // boolean expression.  When this is true, we will
    // change to this state
    
    if(position < 2000) // Put your condition here
    {
      // Write your desired state here
      next_state = STATE_LEFT;
    }
    if(position > 3000) 
    {
      // Write your desired state here
      next_state = STATE_RIGHT;
    }
  }
  if(state == STATE_LEFT)
  {
    // You choose the state to transition to by writing a
    // boolean expression.  When this is true, we will
    // change to this state
    if(position > 2000) // Put your condition here
    {
      // Write your desired state here
      next_state = STATE_FORWARD;
    }
   
  }
 if(state == STATE_RIGHT)
  {
    // You choose the state to transition to by writing a
    // boolean expression.  When this is true, we will
    // change to this state
   
    if(position  < 3000) // Put your condition here
    {
      // Write your desired state here
      next_state = STATE_FORWARD;
      
    }
    if(position < 200 || position > 4800) // Put your condition here
    {
      // Write your desired state here
      next_state = STATE_ALLWHITE;
    }
     if(position > 2400 || position < 2600)// Put your condition here
    {
      // Write your desired state here
      next_state = STATE_ALLBLACK;
    }

 
  }
  if (state == STATE_ALLBLACK)
  {
    int value = randomgen();
    Serial0.println(value);
    delay(3000);
    if(value == 0)
    {
      next_state = STATE_LEFT;
    } else {
      next_state = STATE_RIGHT;
    }
    
  }
  // Add as many of these as required to implement your state tests.
 
  // Once the state selection is complete, update the current state
  state = next_state;

  // This construct is called a swicth statement.  You will learn more
  // about this in later topics.  For now, just copy the pattern if you need to add
  // extra states
  // This selects the state function to execute.  If you add any extra
  // states, they need an entry here - just copy one of the existing blocks
 
  switch(state)
  {
    case STATE_FORWARD:
      stateForward();
      break;

    case STATE_LEFT:
      stateLeft();
      break;

    case STATE_RIGHT:
      stateRight();
      break;

    case STATE_ALLWHITE:
      stateallwhite();
      break;
      
    case STATE_ALLBLACK:
      stateallblack();
      break;
      
    default:
      stateallblack();
  }
}

void pass()
{
  selectState();
  
}

/* -----------END STATE CHOICE---------- */

#include "zumo_driver.h"
