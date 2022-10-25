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

#define STATE_FORWARDDI 5
#define STATE_LEFTDI    6
#define STATE_RIGHTDI   7
#define STATE_HALTDI    8

#define PASS1 0
#define PASS2 1
#define PASS3 2

#define DINS1 0
#define DINS2 1

#define HDINS1 0
#define HDINS2 1
#define HDINS3 2



int step = CREDIT;

bool undone = true;

int state = STATE_FORWARD;

int next_state = STATE_FORWARD;

int passState = PASS1;
int dinstState = DINS1;
int hdinstState = HDINS1;

void stateForward()
{
  Serial.println("forward");
  Serial0.println("forward");
  motors.setSpeeds(SPEED_MAX, SPEED_MAX);
}

void stateBackward()
{
  Serial.println("forward");
  Serial0.println("forward");
  motors.setSpeeds(-SPEED_MAX, -SPEED_MAX);
}

void stateLeft()
{
  Serial.println("left");
  Serial0.println("left");
  motors.setSpeeds(-SPEED_MAX, SPEED_MAX);
}

void stateRight()
{
  Serial.println("right");
  Serial0.println("right");
  motors.setSpeeds(SPEED_MAX, -SPEED_MAX);
}

void stateHalt()
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
    Serial0.println("Head");
  } else
  {
    Serial0.println("Tail");
  }
  return randnum;
}


void stateCoinFlip()
{
  Serial.println("Coin Fliping");
  Serial0.println("Coin Fliping");
  int randnum = randomgen();
  delay(3000);
  if(randnum == 0)
    {
      stateLeft();
      delay(500);
      state = STATE_LEFT;
    } else {
      stateRight();
      delay(500);
      state = STATE_RIGHT;
    }
  } 



void credit()
{
  position = reflectanceSensors.readLine(sensors);

  if(state == STATE_FORWARD)
  {
    if(position > 4900)
    {
      next_state = STATE_HALT;
    } else if (position > 4000) 
    {
      next_state = STATE_RIGHT;
     }
    if(position < 2000)
    {
      next_state = STATE_LEFT;
    }
      


  }

  if(state == STATE_LEFT)
  {
    if(position > 4900)
    {
      next_state = STATE_HALT;
    } else if (position > 3300)
    {
      next_state = STATE_FORWARD;
    }
    

  }
 if(state == STATE_RIGHT)
  {
    if(position  < 3300)
    {
      next_state = STATE_FORWARD;
    }
    if(position > 4900)
    {
      next_state = STATE_HALT;
    }
 
  }

  if(state == STATE_HALT)
  {
    passState = PASS1;
    step = PASS;
    Serial0.print("Changing to Pass");
    
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
    default:
      stateHalt();
  }
}

void pass1() 
{
  
  position = reflectanceSensors.readLine(sensors);
  stateForward();
  if(position > 2400 && position < 2600) 
  {
    stateHalt();
    stateCoinFlip(); 
    passState = PASS2; 
  }
}

void pass2()
{
  position = reflectanceSensors.readLine(sensors);

  if(state == STATE_FORWARD)
  {
    if(position > 4900)
    {
      next_state = STATE_HALT;
    } else if (position > 4000) 
    {
      next_state = STATE_RIGHT;
     }
    if(position < 2000)
    {
      next_state = STATE_LEFT;
    }
      


  }

  if(state == STATE_LEFT)
  {
    if(position > 4900)
    {
      next_state = STATE_HALT;
    } else if (position > 3300)
    {
      next_state = STATE_FORWARD;
    }
    

  }
 if(state == STATE_RIGHT)
  {
    if(position  < 3300)
    {
      next_state = STATE_FORWARD;
    }
    if(position > 4900)
    {
      next_state = STATE_HALT;
    }
 
  }

  if(state == STATE_HALT)
  {
    passState = PASS3;
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
    default:
      stateHalt();
  }
  
}

void pass3()
{
  state = DONE;
}

void pass()
{
  switch(passState)
  {
    case PASS1:
      pass1();
      break;    
    case PASS2:
      pass2();
      break;
    case PASS3:
      stateHalt();
      break;
    default:
      stateHalt();
   }
}

void distin1() 
{
  position = reflectanceSensors.readLine(sensors);
  Serial0.println("It is DINST1");
  Serial0.println(position);
  
  if ( position < 2700 && position > 3300)
 { 
   next_state = STATE_FORWARD;
 }
   if(position > 4900)
   {
    next_state = STATE_FORWARD;
   }

   if (position == 2500)
   {
      stateBackward();
      delay(500);
      dinstState = DINS2;
   }
}

void distin2()
{
  position = reflectanceSensors.readLine(sensors);
  Serial0.println("It is DINST2");
  Serial0.println(position);
  
  if(state == STATE_FORWARD)
  {
    if(position == 2500)
    {
      next_state = STATE_HALT;
    }
    if(position < 4000)
    {
      next_state = STATE_LEFT;
    }


    if(position > 4800)
    {
      next_state = STATE_RIGHT;
    }
    if(sensors[1] > 900 && sensors[4] > 900 && sensors[5] > 900)
    {
//      step = CREDIT;
      
    }


  }
  if(state == STATE_LEFT)
  {
    if(position > 4000)
    {
      next_state = STATE_FORWARD;
    }
    if(sensors[1] > 900 && sensors[4] > 900 && sensors[5] > 900)
    {
//      step = CREDIT;
      
    }

  }
 if(state == STATE_RIGHT)
  {
    if(position  < 4800 ) // Put your condition here
    {
      // Write your desired state here
      next_state = STATE_FORWARD;
    }
    if(sensors[1] > 900 && sensors[4] > 900 && sensors[5] > 900)
    {
//      step = CREDIT;
      Serial0.println("Changing to Credit");
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
      stateBackward();
      break;
      
    default:
      stateHalt();
  }
  
  
  
}

void distin()
{
  switch(dinstState) 
  {
    case DINS1:
      distin1();
      break;
    case DINS2:
      distin2();
      break;
    default:
      stateHalt();      
  }
  
}

void highdistin()
{

}

void functions()
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
