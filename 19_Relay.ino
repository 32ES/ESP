int RELAY_PIN = 27; 

void setup() {
  // Initialize the LED pin as an output
  pinMode(RELAY_PIN, OUTPUT);
 
}

void loop() {
  // Turn the LED on
  digitalWrite(RELAY_PIN, HIGH);
  delay(5000); // Wait for 5 second
  
// Turn the LED on
  digitalWrite(RELAY_PIN, LOW);
  delay(5000); // Wait for 5 second
  
}
