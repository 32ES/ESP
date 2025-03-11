#include <WiFi.h> // Include the WiFi library to enable ESP32 to connect to a WiFi network

// Define your WiFi credentials (network name and password)
char* ssid = "MyWiFiName"; // Replace with your WiFi network name (SSID)
char* password = "MyPassword"; // Replace with your WiFi network password

// Create a WiFi server object that will listen on port 80 (HTTP port)
WiFiServer server(80);

// Variable to store the LED state ("HIGH" or "LOW")
String LED_on_off = "LOW";

// Define the GPIO pin number connected to the LED
const int LEDpin = 2;

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud rate for debugging

  pinMode(LEDpin, OUTPUT); // Set the LED pin as an output
  digitalWrite(LEDpin, LOW); // Ensure the LED is off initially

  // Start the WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { // Wait until the connection is successful
    delay(1000); // Wait 1 second between connection attempts
    Serial.print("Trying to connect to: ");
    Serial.println(ssid); // Print the SSID we are trying to connect to
  }

  // Print connection details when connected
  Serial.println();
  Serial.print("Successful WiFi connection to: ");
  Serial.print(ssid);
  Serial.print(" with IP address: ");
  Serial.println(WiFi.localIP()); // Print the assigned IP address

  server.begin(); // Start the HTTP server
}

void loop() {
  // Check if a client has connected to the server
  WiFiClient My_Client = server.available();

  if (My_Client) { // If a client is available
    Serial.println("Found new WiFi client"); // Print a message for debugging

    String request = ""; // Variable to store the client's HTTP request
    while (My_Client.connected()) { // While the client is connected
      if (My_Client.available()) { // If there is data from the client
        request = My_Client.readStringUntil('\r'); // Read the request until a carriage return ('\r')
        My_Client.read(); // Clear the remaining '\n'

        // Check if the request is to turn the LED on
        if (request.indexOf("GET /GPIO_number/on") >= 0) {
          LED_on_off = "HIGH"; // Update the LED state variable
          digitalWrite(LEDpin, HIGH); // Turn the LED on
        } else if (request.indexOf("GET /GPIO_number/off") >= 0) { // Check if the request is to turn the LED off
          LED_on_off = "LOW"; // Update the LED state variable
          digitalWrite(LEDpin, LOW); // Turn the LED off
        }

        // Send an HTTP response to the client
        My_Client.println("HTTP/1.1 200 OK"); // Send HTTP status code 200 (OK), indicating success
        My_Client.println("Content-type:text/html"); // Specify that the content type is HTML
        My_Client.println("Connection: close"); // Indicate that the connection will close after the response
        My_Client.println(); // Blank line between header and content, required by the HTTP protocol

        // Send HTML content for the web page
        My_Client.println("<!DOCTYPE html><html>"); // Start the HTML document and specify it follows HTML5 syntax
        My_Client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"); // Define responsive behavior for mobile devices
        My_Client.println("<link rel=\"icon\" href=\"data:,\">"); // Set a blank favicon using a data URI
        My_Client.println("<style>"); // Start a style block for CSS
        My_Client.println("html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center; background-color: gray;}"); // Apply styles to the HTML body, including font and background color
        My_Client.println(".button_state1 { background-color: #0000FF; border: none; color: white; padding: 20px 50px; font-size: 30px; cursor: pointer; }"); // Define CSS for the "ON" button. The background color is blue (#0000FF), padding around the text is 20px (vertical) and 50px (horizontal), font size is 30px, and the cursor changes to a pointer when hovered.
        My_Client.println(".button_state2 { background-color: #FFFF00; border: none; color: black; padding: 20px 50px; font-size: 30px; cursor: pointer; }"); // Define CSS for the "OFF" button. The background color is yellow (#FFFF00), padding around the text is 20px (vertical) and 50px (horizontal), font size is 30px, and the cursor changes to a pointer when hovered.
        My_Client.println("a { text-decoration: none; }"); // Remove underline from hyperlinks
        My_Client.println("</style></head>"); // End the CSS block and head section

        My_Client.println("<body>"); // Start the body of the HTML document
        My_Client.println("<br><br>"); // Add two line breaks for spacing
        My_Client.println("<img src=\"https://raw.githubusercontent.com/32ES/ESP/main/Logo%20ESP32.png\" alt=\"ESP32 Logo\" style=\"width:200px;height:auto;\">"); // Add an image with specified width and responsive height
        My_Client.println("<br><br>"); // Add more line breaks for spacing

        // Add a button based on the current LED state
        if (LED_on_off == "LOW") {
          My_Client.println("<p><a href=\"/GPIO_number/on\"><button_state1 class=\"button_state1\">ON</button_state1></a></p>"); // Add a clickable "ON" button with a link to turn the LED on
        } else {
          My_Client.println("<p><a href=\"/GPIO_number/off\"><button_state1 class=\"button_state1 button_state2\">OFF</button_state1></a></p>"); // Add a clickable "OFF" button with a link to turn the LED off
        }

        My_Client.println("</body></html>"); // End the body and the HTML document
        My_Client.println(); // Blank line to indicate end of response
        break; // Exit the loop after sending the response
      }
    }

    My_Client.stop(); // Close the connection with the client
    Serial.println("Client is disconnected"); // Print a message for debugging
  }
}
