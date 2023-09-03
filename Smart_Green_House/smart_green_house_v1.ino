#include "DHT.h"
#define DHTPIN 3 // humidity tempt sensor pin
#define soil_ana_pin  A0	/* Soil moisture sensor O/P pin */
#define soil_dig_pin  2	/* Soil moisture sensor O/P pin */
#define DHTTYPE DHT11 // humidity tempt sensor type
#define threshold_moisture  50
#define threshold_temperature  25 //in celcius
#define threshold_humidity  40
#define range_moisture  10
#define range_temperature  10
#define range_humidity  10

DHT dht(DHTPIN, DHTTYPE);

float moisture_percentage;
int sensor_analog;
int cooler_switch = 8;
int pump_switch = 9;
//int led_red = 4;
//int led_green = 5;
//int led_blue = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);	/* Define baud rate for serial communication */
  dht.begin(); // initialize the sensor
  pinMode(cooler_switch,OUTPUT);
  pinMode(pump_switch,OUTPUT);
  //pinMode(led_red,OUTPUT);
  //pinMode(led_green,OUTPUT);
  //pinMode(led_blue,OUTPUT);

  //digitalWrite(led_red,HIGH);
  //digitalWrite(led_green,HIGH);
  //digitalWrite(led_blue,HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);
  //read soil moisture sensor
  sensor_analog = analogRead(soil_ana_pin);
  sensor_analog = analogRead(soil_dig_pin);
  //convert to suitable units
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  // check if any reads failed (tempt humd sensor) and print results
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
  } 
  else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  "); 

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print(tempF);
    Serial.println("°F");

    
  Serial.print("  |  "); 
  //print soil moisture results
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  
  if(moisture_percentage>=threshold_moisture){
    digitalWrite(pump_switch,HIGH);
    Serial.print("Stopping water pump");
  }
  else if(moisture_percentage<threshold_moisture){
    digitalWrite(pump_switch,LOW);
    Serial.print("Starting water pump");

  }
  if(tempC>threshold_temperature){
    digitalWrite(cooler_switch,LOW);
    Serial.print("Starting cooler");
  }
  else if(tempC<=threshold_temperature){
    digitalWrite(cooler_switch,HIGH);
    Serial.print("Stopping cooler");
  }

}
delay(1000);
}