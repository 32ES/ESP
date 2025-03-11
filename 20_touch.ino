#define LED_PIN 18    // Pin for the LED
#define TOUCH_PIN_ON 4  // Pin for the touch input to turn the LED ON
#define TOUCH_PIN_OFF 15 // Pin for the touch input to turn the LED OFF

bool ledStatus = LOW; // Variable to track the LED status

void setup() {
  // Start the serial monitor for debugging
  Serial.begin(115200);
  
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read touch sensor values
  int touchValueOn = touchRead(TOUCH_PIN_ON);  // Read touch value from GPIO4
  int touchValueOff = touchRead(TOUCH_PIN_OFF); // Read touch value from GPIO15
  
  // Check if touch on GPIO4 is detected (below a certain threshold, e.g., 40)
  if (touchValueOn < 67) {
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
    ledStatus = HIGH;  // Update the LED status
  }
  // Check if touch on GPIO15 is detected (below a certain threshold, e.g., 40)
  else if (touchValueOff < 67) {
    digitalWrite(LED_PIN, LOW);  // Turn off the LED
    ledStatus = LOW;  // Update the LED status
  }

  // Print the status in the same line
  Serial.print("LED Status: ");
  if (ledStatus == HIGH) {
    Serial.print("ON");
  } else {
    Serial.print("OFF");
  }
  Serial.print(" | Touch 1 (GPIO4): ");
  Serial.print(touchValueOn);
  Serial.print(" | Touch 2 (GPIO15): ");
  Serial.println(touchValueOff);
  
  delay(500); // Delay for better readability
}
