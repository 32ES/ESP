int LED_PIN = 2; 

void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
 
}

void loop() {
  // Turn the LED on
  digitalWrite(LED_PIN, HIGH);
  delay(1000); // Wait for 1 second
  
// Turn the LED on
  digitalWrite(LED_PIN, LOW);
  delay(1000); // Wait for 1 second
  
}
