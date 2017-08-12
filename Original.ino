#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
WiFiClient client;

int LED = 13;
int obstaclePin = D1;  // This is our input pin
int hasObstacle = HIGH;  // HIGH MEANS NO OBSTACLE
int amount = 0;
int lastOn = HIGH ;
int ir2 = D2;
int hasObstacle2 = HIGH;  // HIGH MEANS NO OBSTACLE
int totalcar = 0;


char ssid[] = "MyDD2017";
char pass[] = "mydd@2017";

/* Thinkspeak*/
const char* TS_SERVER = "api.thingspeak.com";
String TS_API_KEY ="KAQ72EM76RJ6Z4B9";



void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(obstaclePin, INPUT); 
  Serial.begin(9600);

}

void loop() {

  hasObstacle = digitalRead(obstaclePin); //Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino
  hasObstacle2 = digitalRead(ir2);
  
  // put your main code here, to run repeatedly:
    if(hasObstacle == LOW){
      if(lastOn == HIGH ) {
        amount = amount + 1;
        totalcar = totalcar + 1;
        ThingSpeakUpdate("field1=1&field2="+String(totalcar));
        Serial.println(amount);
        lastOn = LOW;
      }
      else {
        /*nothing*/
      }
    }else {
      if (lastOn == LOW){
        lastOn = HIGH;
      }
      else {
        /*nothing*/
      }
    }
    delay (800);

    // put your main code here, to run repeatedly:
    if(hasObstacle2 == LOW){
      if(lastOn == HIGH ) {
        amount = amount + 1;
        totalcar = totalcar + 1;
        ThingSpeakUpdate("field1=1&field2="+String(totalcar));
        Serial.println(amount);
        lastOn = LOW;
      }
      else {
        /*nothing*/
      }
    }else {
      if (lastOn == LOW){
        lastOn = HIGH;
      }
      else {
        /*nothing*/
      }
    }
    delay (800);
}

/*------------------------------------------------
Sends sensor data to Thingspeak
Inputs: String, data to be entered for each field
Returns: 
------------------------------------------------*/
void ThingSpeakUpdate(String tsData)
{
    Serial.println("Date string: " + tsData);

    Serial.println("...Connecting to Thingspeak");

    // Connecting and sending data to Thingspeak
    if(client.connect("api.thingspeak.com", 80))
    {
        Serial.println("...Connection succesful, updating datastreams");

        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+TS_API_KEY+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(tsData.length());
        client.print("\n\n");

        client.println(tsData); //the ""ln" is important here.

        // This delay is pivitol without it the TCP client will often close before the data is fully sent
        delay(200);

        Serial.println("Thingspeak update sent.");
    }
    else{
        // Failed to connect to Thingspeak
        Serial.println("Unable to connect to Thingspeak.");
    }

    if(!client.connected()){
        client.stop();
    }
    client.flush();
    client.stop();
}

