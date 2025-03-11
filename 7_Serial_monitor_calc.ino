void setup() {
  Serial.begin(115200);
  Serial.println("Enter a number:");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the input as integer number (In Serial monitor choose : "No Line Ending")
    
    int number = Serial.parseInt(); 
    
    // Add 100 to the number
    int result = number + 100;
    
    // Print the result
    Serial.print("Result: ");
    Serial.println(result);
    Serial.println("Enter another number:");

  }
}


