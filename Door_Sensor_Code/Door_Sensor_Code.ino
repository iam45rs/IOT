#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "dhj6fj8rvkd3443vk89vgj";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ASUS_X00TD";
char pass[] = "rahul4056";

bool alarm_mode = false ;
int sensor = 5;  //GPIO Pin number on which sensor is connected
int buzzer = 15; //GPIO Pin number on which buzzer is connected
int alarm_led = 4; //GPIO Pin number on which alarm status led is connected

BlynkTimer timer;

void myTimerEvent(){
   
  if(digitalRead(sensor) == 0){
    Blynk.virtualWrite(V0, "CLOSE");
      
  }
  if(digitalRead(sensor) == 1){
    Blynk.virtualWrite(V0, "OPEN");
    if(alarm_mode == true){
      Blynk.notify("ALERT, Door is open, Alarm Mode ON"); 
      digitalWrite(buzzer, HIGH);        
      }
  }
  }

BLYNK_WRITE(V1) {
  switch (param.asInt()) {
    case 1: { // Item 1
      Serial.println("Item 1 selected");
      alarm_mode = true;
      digitalWrite(alarm_led, HIGH); 
      break;
    }
    case 2: { // Item 2
      Serial.println("Item 2 selected");
      alarm_mode = false;
      digitalWrite(buzzer, LOW);  
      digitalWrite(alarm_led, LOW);  
      break;
    }    
  }
}

void setup()
{
  pinMode(sensor, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(alarm_led, OUTPUT);
  
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  //timer.setInterval(500L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
