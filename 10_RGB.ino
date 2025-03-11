int LED_PIN_R = 18; 
int LED_PIN_G = 19;
int LED_PIN_B = 21;

void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  
}

void loop() {
  digitalWrite(LED_PIN_R, HIGH);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_B, LOW);
  delay(1000); // Wait for 1 second
  
  digitalWrite(LED_PIN_R, LOW);
  digitalWrite(LED_PIN_G, HIGH);
  digitalWrite(LED_PIN_B, LOW);
  delay(1000); // Wait for 1 second
  
  digitalWrite(LED_PIN_R, LOW);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_B, HIGH);
  delay(1000); // Wait for 1 second
  
}
