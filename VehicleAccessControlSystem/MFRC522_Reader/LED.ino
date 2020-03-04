void LEDsetup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  digitalWrite(redLED, LED_OFF);  
  digitalWrite(greenLED, LED_OFF);  
  digitalWrite(yellowLED, LED_OFF); 

}
