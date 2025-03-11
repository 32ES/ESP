
// Define GPIO pins
#define LED_PIN 18 // GPIO connected to the LED
#define LDR_PIN 4  // GPIO connected to the LDR (analog input)

// Define the threshold voltage (0.2V)
#define THRESHOLD_VOLTAGE 0.2

void setup() {
  // Initialize the serial communication for debugging (optional)
  Serial.begin(115200);

  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Initialize the LED state to OFF
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read the analog value from the LDR
  int ldrValue = analogRead(LDR_PIN);

  // Convert the analog value to voltage
  float voltage = (ldrValue / 4095.0) * 3.3; // Assuming a 12-bit ADC and 3.3V reference

  // Print the voltage to the serial monitor for debugging
  Serial.print("LDR Voltage: ");
  Serial.println(voltage);

  // Check if the voltage exceeds the threshold
  if (voltage > THRESHOLD_VOLTAGE) {
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
    Serial.println("LED ON");
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off the LED
    Serial.println("LED OFF");
  }

  // Add a small delay to avoid spamming the serial monitor
  delay(100);
}
