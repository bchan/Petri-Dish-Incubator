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
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" degC");

  // Second Line
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

//  if (tempC < 34.5) {
//    digitalWrite(pinOut, HIGH);
//  } else {
//    digitalWrite(pinOut, LOW);
//  }


// if (firstRun == 0) {
//    if (tempC < 36) {
//      digitalWrite(pinOut, HIGH);
//    }
//  
//    if (tempC > 34) {
//      digitalWrite(pinOut, LOW);
//      firstRun++;
//    }
//    
//  } else if (firstRun > 1) {
//    if (tempC < 36.5) {
//      digitalWrite(pinOut, HIGH);
//      startCount = true;
//    }
//  
//    if (tempC > 36 && counter == 40) {
//      digitalWrite(pinOut, LOW);
//      counter = 0;
//      startCount = false;
//    }
//
//    if (startCount) {
//      counter++;
//    }
//
//    
//  }
  if (firstRun == 0) {
    if (tempC < 36) {
      digitalWrite(pinOut, HIGH);
    }
  
    if (tempC > 34) {
      digitalWrite(pinOut, LOW);
      firstRun++;
    }
    
  } else if (firstRun > 1) {
    if (tempC < 36.5 && startCount == false) {
      digitalWrite(pinOut, HIGH);
      startCount = true;
    }

    if (counter == 20) {
      if (tempC < 35.8) {
        counter = 0;
      } else {
        digitalWrite(pinOut, LOW);
        startCount = false;
        counter = 0;
      }
    }

    if (startCount) {
      counter++;
    }

    
  }

  if (firstRun == 1 && tempC > 36) {
    firstRun++;
  }
  
  

  delay(1000);

}
