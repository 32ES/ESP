#include <WiFi.h>
#include <Firebase_ESP_Client.h>

int myLED = 0;
int LEDpin = 2;
float count1 = 3.22;
unsigned long Timecount = 0;

#define WIFI_SSID "YOUR_WIFI_NAME"                //Your Wifi network name
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"        //Your Wifi password
#define API_KEY "API_KEY_FROM_FIREBASE"           //Firebase API KEY
#define DATABASE_URL "DATABASE_URL_FROM_FIREBASE" //Firebase database URL
#define USER_EMAIL "USER_EMAIL"                   //User email
#define USER_PASSWORD "USER_PASSWORD"             //User password

FirebaseData fbdo,fbdo2;
FirebaseAuth auth;
FirebaseConfig config;


void setup()
{
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
    Timecount = millis();
    Firebase.RTDB.setFloat(&fbdo, "/Myfirebase/temperature", count1++);

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
