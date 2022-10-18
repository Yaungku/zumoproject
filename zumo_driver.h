
void setup()
{
  //Setup the local serial interface
  Serial.begin(9600);

  //Setup the wireless interface
  Serial0.begin(115200);
  
  // Initialize the reflectance sensors module
  reflectanceSensors.init();
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);        // turn on LED to indicate we are in calibration mode
  
  unsigned long startTime = millis();
  while(millis() - startTime < 10000)   // make the calibration take 10 seconds
  {
    reflectanceSensors.calibrate();
  }
  digitalWrite(13, LOW);         // turn off LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (byte i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(reflectanceSensors.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (byte i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(reflectanceSensors.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  // Finish editing here--------
  Serial.println("calibration complete");
  Serial0.println("calibration complete");

  // Turn off LED to indicate we are through with calibration
  digitalWrite(13, LOW);
  
  // Wait for the user button to be pressed and released
  Serial.println("ready to begin");
  Serial0.println("ready to begin");
  button.waitForButton();
  Serial0.println(map(analogRead(0), 0, 1023, 0, 6));
  Serial0.print(" V");
  Serial.println("start");
  Serial0.println("start");

  // Delay for one second
  delay(1000);
}


void loop()
{
  pass();
  delay(50);
}
