#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif
#include <Wire.h>
#include "ESP32_MailClient.h"
// REPLACE WITH YOUR NETWORK CREDENTIALS

#define emailSenderAccount    "ghuyniot@gmail.com"    
#define emailSenderPassword   "weekndcold1"
#define emailRecipient        "nguyenkhaikh321@gmail.com"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "NodeWifi32 Test"
#define RXD2 16
#define TXD2 17
#define LED 2
// The Email Sending data object contains config and data to send
SMTPData smtpData;
// Callback function to get the Email sending status

//Access point credentials
const char* ssid = "Sinh Vien Home";
const char* password = "06117370";
const char* host = "http://dighuyniot.tech";
String get_host = "http://dighuyniot.tech";
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 3000000; 
int check=0;
char buff[10];
char str1='1';
char str2='0';
volatile byte indx;
const char* serverName = "http://192.168.1.17:81/demo/postdemo1.php";
String apiKeyValue = "tPmAT5Ab3j7F9";

WiFiServer server(80);  // open port 80 for server connection
void sendCallback(SendStatus info);
  void setup() {
    // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
    Serial.begin(115200);
    //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    pinMode(LED,OUTPUT);
  WiFi.begin(ssid, password);
    //starting the server
    server.begin();
    startMillis = millis();
  }
   void loop()
{post_btn("onl1","light1");}

void post_btn(String device,String value){
  //Check WiFi connection status
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + device
                           + "&value2=" + value + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&value1=24.75&value2=49.54&value3=1005.14";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
    
    if (httpResponseCode>0) {
      String respone=http.getString();
      Serial.println(respone);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  
 //Send an HTTP POST request every 30 seconds
}
