#include "DHT.h"
#include "Wire.h"
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// DHT Pins
#define DHTPIN 2
#define DHTTYPE DHT22

// One Wire
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);

// Sensors
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
DallasTemperature tempSensor(&oneWire);

// DHT Sensor Variables
float humidity;
float dhtTemperature;
float heatIndex;

// Temperature Sensor Variables
float tempC;
float tempF;

int pinOut = 10;

void setup() {
  // Starting Sensors and LCD
  Serial.begin(9600);
  tempSensor.begin();
  dht.begin();
  lcd.init();
  lcd.init();
  lcd.backlight();


  // Printing Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("Toothbrush");
  lcd.setCursor(0, 1);
  lcd.print("Industries");
  
  delay(2000);

  lcd.setCursor(0, 0);
  lcd.print("Presents        ");
  lcd.setCursor(0, 1);
  lcd.print("...             ");

  delay(2000);

  lcd.setCursor(0, 0);
  lcd.print("Petri Dish");

  lcd.setCursor(0, 1);
  lcd.print("Incubator");

  pinMode(pinOut, OUTPUT);

  delay(2000);

  
}

int firstRun = 0;
int counter = 0;
bool startCount = false;

void loop() {
  // DHT Sensor Values
  humidity = dht.readHumidity();
  dhtTemperature = dht.readTemperature();
  heatIndex = dht.computeHeatIndex(dhtTemperature, humidity, false);

  // Temperature Sensor Values
  tempSensor.requestTemperatures();
  tempC = tempSensor.getTempCByIndex(0);
  tempF = tempSensor.toFahrenheit(tempC);

  // First Line
  lcd.setCursor(0, 0);
  lcd.print("Tw:");
  lcd.print(tempC, 1);
  lcd.print(" Tc:");
  lcd.print(dhtTemperature, 1);

  // Second Line
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

// Code for Regulating Water
//  if (firstRun == 0) {
//    if (tempC < 36) {
//      digitalWrite(pinOut, HIGH);
//    }
//
//    if (tempC > 35) {
//      digitalWrite(pinOut, LOW);
//      startCount = true;
//      firstRun++;
//    }
//  } else {
//    if (tempC > 36.3) {
//      digitalWrite(pinOut, LOW);
//      counter = 0;
//    }
//    if (counter > 5) {
//      if (tempC < 36.3) {
//        if (counter == 10){
//          counter = 0;          
//        }
//        digitalWrite(pinOut, HIGH);
//      } else {
//        counter = 0;
//        digitalWrite(pinOut, LOW);
//      }
//    } else {
//        digitalWrite(pinOut, LOW);
//    }
//
//    counter++;
//  }

// Code for Regulating Air
  if (firstRun == 0) {
    if (dhtTemperature < 36) {
      digitalWrite(pinOut, HIGH);
    }

    if (dhtTemperature > 35) {
      digitalWrite(pinOut, LOW);
      startCount = true;
      firstRun++;
    }
  } else {
    if (dhtTemperature > 36.3) {
      digitalWrite(pinOut, LOW);
      counter = 0;
    }
    if (counter > 5) {
      if (dhtTemperature < 36.3) {
        if (counter == 10){
          counter = 0;          
        }
        digitalWrite(pinOut, HIGH);
      } else {
        counter = 0;
        digitalWrite(pinOut, LOW);
      }
    } else {
        digitalWrite(pinOut, LOW);
    }

    counter++;
  }  

  delay(1000);

}
