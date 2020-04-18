/*
 * Project IOTArgon
 * Description:
 * Author:
 * Date:
 */
#include "MQTT.h"
#include <time.h>

String deviceID = System.deviceID();

byte server[] ={192,168,7,31}; //ip adress of the mqtt broker

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.printf("Callback");
}
MQTT client(server, 1883, callback); //port of the mqtt broker

const char *message;
void meshcallback(const char *event, const char *data)
{
	
	if (client.isConnected() && data) {
        client.publish("data",data);
		Serial.println(data);
		Serial.println("published");
    }
	else{
		if(!data){
			Serial.println("Data Error");
		}
		else
		{
			Serial.println("Server not found");
		}
		client.connect(deviceID);
	}   
}

void setup()
{
	Serial.begin(9600);
	Time.zone(1);
	Serial.println(System.deviceID());
	Particle.syncTime();
  	waitUntil(Particle.syncTimeDone);
	Serial.print("ip: ");
	Serial.println(WiFi.localIP());
	client.connect(deviceID);
}

void loop()
{
 	Mesh.subscribe("sensorData", meshcallback);
	delay(500);
}