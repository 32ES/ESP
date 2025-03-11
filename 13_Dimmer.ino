// GPIO definitions
const int analogInputPin = 4;  // Analog input pin GPIO4
const int pwmOutputPin = 18;   // PWM output pin GPIO18

void setup() {
  // Configure analog input
  pinMode(analogInputPin, INPUT);

  // Configure PWM output
  pinMode(pwmOutputPin, OUTPUT);
}

void loop() {
  // Read the analog value from the input pin
  int analogValue = analogRead(analogInputPin);  // Values range from 0 to 4095

  // Map the analog value to a PWM value
  int pwmValue = map(analogValue, 0, 4095, 0, 255);  // Map range 0-4095 to 0-255

  // Write the PWM value to the output pin
  analogWrite(pwmOutputPin, pwmValue);

  // Short delay for stability
  delay(10);
}
