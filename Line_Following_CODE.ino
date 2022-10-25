#include "zumo_state.h"

#define SPEED_MAX 200
#define SPEED_HALT 0

#define PASS 0
#define CREDIT    1
#define DISTIN   2
#define HIGHDISTIN    3
#define DONE 4

#define STATE_FORWARD 0
#define STATE_LEFT    1
#define STATE_RIGHT   2
#define STATE_HALT    3
#define COINFLIP      4
#define STATE_FORWARDDI 5
#define STATE_LEFTDI    6
#define STATE_RIGHTDI   7
#define STATE_HALTDI    8

int step = PASS;

int state = STATE_FORWARD;

int next_state = STATE_FORWARD;

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

void stateHalt()
{
  Serial.println("halt");
  Serial0.println("halt");
  motors.setSpeeds(SPEED_HALT, SPEED_HALT);
}

void stateCoinFlip()
{
  Serial.println("Coin Fliping");
  Serial0.println("Coin Fliping");
  int randnum = randomgen();
  if(value == 0)
    {
      motors.setSpeeds(-SPEED_MAX, SPEED_MAX);
    } else {
      motors.setSpeeds(SPEED_MAX,- SPEED_MAX);
    }
}

int randomgen()
{
  int randnum = random(2);
  Serial.println(randnum);
  if(randnum == 1)
  {
    Serial0.println("Head");
  } else
  {
    Serial0.println("Tail");
  }
  return randnum;
}


void selectState()
{
  position = reflectanceSensors.readLine(sensors);

  if(state == STATE_FORWARD)
  {
    if(position == 2500)
    {
      next_state = STATE_HALT;
    }
    if(position < 2000)
    {
      next_state = STATE_LEFT;
    }


    if(position > 4000)
    {
      next_state = STATE_RIGHT;
  }


  }


  if(state == STATE_LEFT)
  {
    if(position == 2500)
    {
      next_state = STATE_HALT;
    }
    if(position > 3300)
    {
      next_state = STATE_FORWARD;
    }

  }
 if(state == STATE_RIGHT)
  {
    if(position == 2500)
    {
      next_state = STATE_HALT;
    }
    if(position  < 3300) // Put your condition here
    {
      // Write your desired state here
      next_state = STATE_FORWARD;
    }


  }
  if (state == STATE_HALT)
  {

  }
  state = next_state;

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

    case STATE_HALT:
      stateHalt();
      break;
    case COINFLIP:
      stateCoinFlip();
      break;
    default:
      stateHalt();
  }
}

void pass()
{
  selectState();

}

void credit()
{

}

void distin()
{
 void stateForwardDI()
{
  Serial.println("forwardDI");
  Serial0.println("forwardDI");
  motors.setSpeeds(SPEED_MAX, SPEED_MAX);
}

void stateLeftDI()
{
  Serial.println("leftDI");
  Serial0.println("leftDI");
  motors.setSpeeds(SPEED_HALT, SPEED_MAX);
}

void stateRightDI()
{
  Serial.println("rightDI");
  Serial0.println("rightDI");
  motors.setSpeeds(SPEED_MAX, SPEED_HALT);
}

void stateHaltDI()
{
  Serial.println("haltDI");
  Serial0.println("haltDI");
  motors.setSpeeds(SPEED_HALT, SPEED_HALT);
}

void selectState()
{
  position = reflectanceSensors.readLine(sensors);

  if(state == STATE_FORWARDDI)
  {
    if(position == 2500)
    {
      next_state = STATE_HALTDI;
    }
    if(position > 1400)
    {
      next_state = STATE_LEFTDI;
    }


    if(position < 1000)
    {
      next_state = STATE_RIGHTDI;
  }


  }
  if(state == STATE_LEFTDI)
  {
    if(position == 2500)
    {
      next_state = STATE_HALTDI;
    }
    if(position < 1400)
    {
      next_state = STATE_FORWARDDI;
    }

  }
 if(state == STATE_RIGHTDI)
  {
    if(position == 2500)
    {
      next_state = STATE_HALTDI;
    }
    if(position  > 1000 ) // Put your condition here
    {
      // Write your desired state here
      next_state = STATE_FORWARDDI;
    }


  }
  if (state == STATE_HALT)
  {

  }
  state = next_state;
  }
  
  }
  state = next_state;

switch(state)
  {
    case STATE_FORWARDDI:
      stateForwardDI();
      break;

    case STATE_LEFTDI:
      stateLeftDI();
      break;

    case STATE_RIGHTDI:
      stateRight();
      break;

    case STATE_HALTDI:
      stateHaltDI();
      break;
      
    default:
      stateHalt();
  }
  
  if(position == 3000);
}

void highdistin()
{
 
}
void Functions()
{
  switch(step)
  {
    case HIGHDISTIN:
      highdistin();
      break;

    case DISTIN:
      distin();
      break;

    case CREDIT:
      credit();
      break;

    case PASS:
      pass();
      break;
    case DONE:
      stateHalt();
      break;
    default:
      stateHalt();
  }
}

#include "zumo_driver.h"


