#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WifiClientSecure.h>
#include <WiFiManager.h>




#define LED_PIN D5
#define SENSOR_PIN D8
int sensorValue;

const char* ssid = "Horký beďar";
const char* password = "33333333";
String serverName = "https://www.bartosek.cz/shared/testEnv/OFD-API-ESP8266/api/";
String secret = "1234567890";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

WiFiManager wifiManager;
LiquidCrystal_I2C lcd(0x27, 16, 2);
// lcd.setCursor(´Pozice na řádku, řádek´);





void setup() {

  Serial.begin(9600);

  wifiManager.autoConnect("AutoConnectAP");




  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to " +  String(timerDelay/1000) + " seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");






  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);

  digitalWrite(LED_PIN, HIGH);



  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Starting...");
  lcd.setCursor(0,1);
  lcd.print("github/Will-Bee");
  delay(2000);
  lcd.clear();

  digitalWrite(LED_PIN, LOW);

  lcd.setCursor(0,0);
  lcd.print("Sensor value: ");
}


void request(bool _state) {

  String state = _state ? "True" : "False";

  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;

  String serverPath = serverName + "?secret=" + secret + "&switch=" + state;

  http.begin(client, serverPath.c_str());

  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

}



void loop() {

  sensorValue = digitalRead(SENSOR_PIN);

  digitalWrite(LED_PIN, sensorValue);

  lcd.setCursor(0,1);
  lcd.print(sensorValue);

  request(sensorValue);

}