#define BLYNK_PRINT Serial   
#include <SPI.h>    // For communicating with one or more devices simultaneously over short distances
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define BLYNK_PRINT Serial


char auth[] ="eh7h36nd93bjd877ui8";               //Authentication code sent by Blynk
char ssid[] = "ASUS_X00TD";                       //WiFi SSID
char pass[] = "rahul4056";                       //WiFi Password

#define sensorPin D3 
int sensorState = 0;
int lastState = 0;
#define DHTPIN 2    
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
   pinMode(sensorPin, INPUT);
  dht.begin();

}


int sensor=0;
void sendTemps()
{
sensor=analogRead(A0);
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0); 
Serial.println(temp);
Serial.println(sensor);
Blynk.virtualWrite(V1, temp);
Blynk.virtualWrite(V2,sensor);
delay(1000);
}


void loop()
{
  Blynk.run(); 
  timer.run(); 
  sendTemps();
  sensorState = digitalRead(sensorPin);
Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) {
  Serial.println("needs water, send notification");
  Blynk.notify("Water your plants");
  lastState = 1;
  delay(1000);
//send notification
    
  } 
  else if (sensorState == 1 && lastState == 1) {
    //do nothing, has not been watered yet
  Serial.println("has not been watered yet");
  delay(1000);
  }
  else {
    //st
    Serial.println("does not need water");
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
}
