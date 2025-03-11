// Include necessary libraries for Wi-Fi and DHT sensor functionality
#include <WiFi.h>           // Library to enable Wi-Fi functionality
#include <DHT.h>            // Install DHT sensor by adafruit

// Wi-Fi credentials
const char* ssid = "MyNetwork";       // Replace with your Wi-Fi network name (SSID)
const char* password = "MyPassword"; // Replace with your Wi-Fi network password

// DHT sensor setup
#define DHTPIN 4         // GPIO pin on the ESP32 connected to the DHT11 data pin
#define DHTTYPE DHT11    // Define the type of DHT sensor being used (DHT11)
DHT dht(DHTPIN, DHTTYPE); // Create a DHT sensor object with the specified pin and type

// Create an instance of the WiFiServer to listen for incoming connections on port 80
WiFiServer server(80);

// Variables to store sensor readings
float temperature = 0.0; // Variable to store the temperature reading
float humidity = 0.0;    // Variable to store the humidity reading

// Function to read data from the DHT11 sensor
void readDHTSensor() {
  // Read temperature in Celsius from the DHT sensor
  float t = dht.readTemperature();
  // Read humidity as a percentage from the DHT sensor
  float h = dht.readHumidity();

  // Check if the readings are valid (not NaN)
  if (!isnan(t) && !isnan(h)) {
    temperature = t; // Update the temperature variable with the new reading
    humidity = h;    // Update the humidity variable with the new reading
  } else {
    // Print an error message to the Serial Monitor if the sensor fails to provide valid data
    Serial.println("Failed to read from DHT sensor!");
  }
}

// Function to create an HTML page to be served to clients
String createHTML() {
  // Start building the HTML response
  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<title>ESP32 DHT11 Monitor</title>"; // Set the page title
  html += "<style>"; // Add CSS styles for the page
  html += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f9; color: #333; }";
  html += "h1 { font-size: 5em; margin: 20px; }";
  html += "p { font-size: 4em; margin: 10px 0; }";
  html += "img { margin: 40px auto; width: 600px; }";
  html += "#temp, #hum { font-weight: bold; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>ESP32 DHT11 Monitor</h1>"; // Display the page header
  html += "<img src=\"https://raw.githubusercontent.com/32ES/ESP/main/Logo%20ESP32.png\" alt=\"ESP32 Logo\">"; // Add an ESP32 logo
  // Display the temperature and humidity readings
  html += "<p>Temperature: <span id='temp'>" + String(temperature) + "</span> °C</p>";
  html += "<p>Humidity: <span id='hum'>" + String(humidity) + "</span> %</p>";
  html += "<script>";
  html += "setInterval(function() {";
  html += "  fetch('/data').then(response => response.text()).then(data => {";
  html += "    const parsedData = JSON.parse(data);";
  html += "    document.getElementById('temp').innerText = parsedData.temperature ;";
  html += "    document.getElementById('hum').innerText = parsedData.humidity ;";
  html += "  });";
  html += "}, 2000);"; // Update data every 2 seconds
  html += "</script>";
  html += "</body></html>"; // End the HTML document
  return html; // Return the complete HTML string
}

// Function to handle the request for sensor data
String handleSensorData() {
  // Create a JSON-like response with temperature and humidity values
  String data = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
  return data;
}

// Setup function, runs once at startup
void setup() {
  // Start the serial monitor for debugging purposes
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();

  // Connect to the specified Wi-Fi network
  WiFi.begin(ssid, password);
  // Wait until the ESP32 is connected to the Wi-Fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // Wait for 1 second
    Serial.println("Connecting to WiFi..."); // Print connection status to the Serial Monitor
  }
  // Print a success message when connected to Wi-Fi
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the ESP32's IP address on the Serial Monitor

  // Start the web server to handle incoming requests
  server.begin();
}

// Loop function, runs continuously
void loop() {
  // Read the sensor data every 0.5 seconds
    delay(500);
    readDHTSensor(); // Call the function to read sensor data
  

  // Check if a client has connected to the web server
  WiFiClient client = server.available();
  if (client) {
    // Read the incoming HTTP request from the client
    String request = client.readStringUntil('\r');
    Serial.println(request); // Print the request to the Serial Monitor for debugging
    client.flush(); // Clear the request buffer

    // If the request is for the root path ('/'), send the HTML page
    if (request.indexOf("GET / ") != -1) {
      client.print("HTTP/1.1 200 OK\r\n"); // HTTP response header
      client.print("Content-Type: text/html\r\n"); // Specify that the response contains HTML
      client.print("Connection: close\r\n\r\n"); // Close the connection after sending the response
      client.print(createHTML()); // Send the HTML content
    }
    // If the request is for '/data', send the sensor data in a JSON-like format
    else if (request.indexOf("GET /data") != -1) {
      client.print("HTTP/1.1 200 OK\r\n");
      client.print("Content-Type: application/json\r\n");
      client.print("Connection: close\r\n\r\n");
      client.print(handleSensorData()); // Send the sensor data
    }

    client.stop(); // Disconnect the client
  }
}
