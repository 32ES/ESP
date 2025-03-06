//Install dht sensor adafruit (By adafruit) and all dependences (Also includes adafruit unified sensor)
//Install adafruit unified sensor (By adafruit)

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#define DHTPIN 4              // DHT GPIO
#define DHTTYPE    DHT11      // Define DHT type as DHT11

DHT dht(DHTPIN, DHTTYPE);    

int myLED = 0;
int LEDpin = 2;
float count1 = 3.23;
unsigned long Timecount = 0;

#define WIFI_SSID "Your_SSID"                //Your Wifi network name
#define WIFI_PASSWORD "Your_wifi_password"        //Your Wifi password
#define API_KEY "your_api"           //Firebase API KEY
#define DATABASE_URL "your_URL" //Firebase database URL
#define USER_EMAIL "email"                   //User email
#define USER_PASSWORD "email_password"             //User password

FirebaseData fbdo,fbdo2;
FirebaseAuth auth;
FirebaseConfig config;

void setup()
{
  //Start the temperature sensor
  dht.begin();
  
  pinMode(LEDpin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Waiting for Wifi connection");
    delay(500);
  }
  Serial.print("WiFi connected, IP = ");
  Serial.println(WiFi.localIP());
  
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;

  Firebase.reconnectNetwork(true); //ESP32 will try to re-connect automaticly to WiFi in case of that the connection drops
  Firebase.begin(&config, &auth);
  Firebase.RTDB.beginStream(&fbdo2,"/Myfirebase/LED");
}

void loop()
{

  if (Firebase.ready() && (millis()-Timecount > 1000 || Timecount == 0))
  {
    float t = dht.readTemperature();
    Timecount = millis();
    Firebase.RTDB.setFloat(&fbdo, "/Myfirebase/temperature", t);
  }

if (Firebase.ready()){
  if(!Firebase.RTDB.readStream(&fbdo2)){
    Serial.println("error stream");  
  }
    
if(fbdo2.streamAvailable()){
  Serial.println("New stream");
    if(fbdo2.dataType() == "int"){
      myLED = fbdo2.intData();
      Serial.println(myLED);
    }
    
  if(myLED == 0){
    digitalWrite(LEDpin,LOW);
  }
  else{
    digitalWrite(LEDpin,HIGH);
  }
}

}

}
