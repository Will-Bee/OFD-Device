#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


#define LED_PIN D5
#define SENSOR_PIN D8
int sensorValue;


LiquidCrystal_I2C lcd(0x27, 16, 2);


// lcd.setCursor(´Pozice na řádku, řádek´);



void setup() {

  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);

  digitalWrite(LED_PIN, HIGH);

  Serial.begin(9600);

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

void loop() {

  digitalWrite(LED_PIN, digitalRead(SENSOR_PIN));

  lcd.setCursor(0,1);
  lcd.print(digitalRead(SENSOR_PIN));

}