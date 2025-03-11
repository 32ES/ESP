// Include necessary libraries
// (No additional libraries are required for basic GPIO control in Arduino IDE)

// Define the GPIO pin connected to the passive buzzer
#define BUZZER_PIN 18

void setup() {
  // Initialize the serial communication for debugging (optional)
  Serial.begin(115200);

  // Set the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Generate a tone by toggling the GPIO pin
  for (int i = 0; i < 1000; i++) { // Adjust the loop count for tone duration
    digitalWrite(BUZZER_PIN, HIGH); // Set the pin HIGH
    delayMicroseconds(500); // Adjust the delay for tone frequency (e.g., 500us for 1kHz)
    digitalWrite(BUZZER_PIN, LOW); // Set the pin LOW
    delayMicroseconds(500); // Maintain the same delay for consistency
  }
  Serial.println("Buzzer played tone"); // Debug message

  // Wait for 1 second (1000 milliseconds) before playing the tone again
  delay(1000);
}


/*
// Include necessary libraries
// (No additional libraries are required for basic GPIO control in Arduino IDE)

// Define the GPIO pin connected to the active buzzer
#define BUZZER_PIN 18

void setup() {
  // Initialize the serial communication for debugging (optional)
  Serial.begin(115200);

  // Set the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Turn the buzzer on by setting the GPIO pin HIGH
  digitalWrite(BUZZER_PIN, HIGH);
  Serial.println("Buzzer ON"); // Debug message

  // Wait for 1 second (1000 milliseconds)
  delay(1000);

  // Turn the buzzer off by setting the GPIO pin LOW
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("Buzzer OFF"); // Debug message

  // Wait for 1 second (1000 milliseconds)
  delay(1000);
}
*/