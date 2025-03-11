
//Install adafruit SSD1306 (By adafruit) and all dependencies (Also includes adafruit gfx)
//Install adafriut gfx (By adafruit)
//Install dht sensor adafruit (By adafruit) and all dependences (Also includes adafruit unified sensor)
//Install adafruit unified sensor (By adafruit)

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>

#define DHTPIN 4              // DHT GPIO
#define DHTTYPE    DHT11      // Define DHT type as DHT11

DHT dht(DHTPIN, DHTTYPE);    

//Define the display size
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128 // OLED display width, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  //Start the temperature sensor
  dht.begin();
  //Start the display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    Serial.println(F("Display failed"));
  }
  
}
void loop() {
  delay(100);
  float t = dht.readTemperature();

  display.clearDisplay();             //Clear the display
  display.setTextSize(1);             //Set the text size
  display.setTextColor(WHITE);        //Set the color
  display.setCursor(22, 20);          //Set the cursor position
  display.print("Temperature:");      //Send text to the cursor position
  display.setTextSize(2);             //Change text size
  display.setCursor(30, 35);          //Set the cursor position
  display.print(t);                   //Print the temperature
  display.display();                  //Send all the commands to the dislplay
  Serial.print("Temperature = ");
  Serial.println(t);
  delay(100);
}
