// Define GPIO pins
#define LED_PIN 18 // GPIO connected to the LED
#define IR_PIN 4   // GPIO connected to the IR sensor (digital output)

void setup() {
  // Initialize the serial communication for debugging (optional)
  Serial.begin(115200);

  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Set the IR pin as an input
  pinMode(IR_PIN, INPUT);

  // Initialize the LED state to OFF
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read the digital value from the IR sensor
  int irValue = digitalRead(IR_PIN);

  // Print the IR sensor state to the serial monitor for debugging
  Serial.print("IR Sensor State: ");
  Serial.println(irValue);

  // Check the IR sensor state
  if (irValue == HIGH) {
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
    Serial.println("LED ON");
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off the LED
    Serial.println("LED OFF");
  }

  // Add a small delay to avoid spamming the serial monitor
  delay(100);
}
