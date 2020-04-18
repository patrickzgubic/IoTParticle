/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/projects/IOTXenon/src/IOTXenon.ino"
/*
 * Project IOTXenon
 * Description:
 * Author:
 * Date:
 */

#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "MQTT.h"
#include <time.h>
void callback(char* topic, byte* payload, unsigned int length);
void setup();
void loop();
#line 11 "c:/projects/IOTXenon/src/IOTXenon.ino"
#define DHTPIN 	A2     // set pin


String deviceID = System.deviceID();
DHT dht(DHTPIN);
void callback(char* topic, byte* payload, unsigned int length) {
	Serial.printf("Callback");
}

void setup()
{
	Serial.begin(9600);
	Time.zone(1);
	Serial.println(System.deviceID());
	Particle.syncTime();
  	waitUntil(Particle.syncTimeDone);
	dht.begin();
	Mesh.connect();
}

void loop()
{
	float temp, humidity;
	temp = dht.getTempCelcius();
	humidity = dht.getHumidity();
	time_t timestamp = Time.now();
	char message[217];	
	sprintf(message,"{\"deviceID\":\"%s\",\"timestamp\":\"%s\",\"temperature\":%f,\"tempUnit\":\"%c\",\"humidity\":%f,\"humUnit\":\"%c\"}",System.deviceID().c_str(),Time.format(timestamp, TIME_FORMAT_ISO8601_FULL).c_str(),temp,'C',humidity,'%');
	Serial.printlnf("%s",message);
	Mesh.publish("sensorData",message);
	Serial.println("published");
	delay(1000);
}