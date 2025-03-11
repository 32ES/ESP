int ledPin = 18;     
int buttonPin = 4;  

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  digitalWrite(ledPin, LOW);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    Serial.println("Button pressed");
  } else {
    digitalWrite(ledPin, LOW);  // Turn off the LED
    Serial.println("Button released");
  }
}
