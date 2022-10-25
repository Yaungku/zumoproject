void setup()
{
  //Setup the local serial interface
  Serial.begin(9600);

  //Setup the wireless interface
  Serial0.begin(115200);

  // Initialize the reflectance sensors module
  reflectanceSensors.init();

  button.waitForButton();
  Serial0.println("The battery voltage is ");
  int batteryvalue = map(analogRead(0), 0, 1023, 0,6);
  Serial0.println(batteryvalue);
  Serial0.println(" V");
  if (batteryvalue == 6) {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
    reflectanceSensors.calibrate();

    delay(20);
  }
  motors.setSpeeds(0,0);

  digitalWrite(13, LOW);

  // Wait for the user button to be pressed and released
  button.waitForButton();
  Serial0.println("The battery voltage is ");
  Serial0.print(batteryvalue);
  Serial0.println(" V");
  delay(1000);
  } else {
    Serial0.println("The battery is low");
  }
}


void loop()
{
  functions();
  delay(50);
}
