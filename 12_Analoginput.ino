const int analogPin = 4;  // GPIO4 connected to analog input
const int ledPin = 18;    // GPIO18 connected to LED
const float threshold = 1.0; // Voltage threshold (1 volt)

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  pinMode(ledPin, OUTPUT);  // Set GPIO18 as output
}

void loop() {
  int analogValue = analogRead(analogPin); // Read from the analog input
  float voltage = analogValue * (3.3 / 4095.0); // Convert ADC value to voltage (assuming 3.3V reference and 12-bit ADC)

  Serial.print("Voltage: ");
  Serial.println(voltage); // Print the voltage to the serial monitor

  if (voltage > threshold) {
    digitalWrite(ledPin, HIGH); // Turn on the LED if the voltage exceeds 1 volt
  } else {
    digitalWrite(ledPin, LOW); // Turn off the LED
  }

  delay(500); // Short delay for sampling
}
