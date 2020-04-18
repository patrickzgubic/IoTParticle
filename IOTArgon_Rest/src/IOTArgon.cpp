/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/projects/IOTArgon_Rest/src/IOTArgon.ino"
/*
 * Project IOTArgon
 * Description:
 * Author:
 * Date:
 */

#include <time.h>
#include "HttpClient.h"

	void meshcallback(const char *event, const char *data);
void setup();
void loop();
#line 11 "c:/projects/IOTArgon_Rest/src/IOTArgon.ino"
HttpClient http;
	http_request_t request;
	http_response_t response;
	http_header_t headers[] = {
		{ "Accept" , "application/vnd.kafka.v2+json"},
		{ "Content-Type", "application/vnd.kafka.avro.v2+json"},
		{ NULL, NULL } //terminate the header
	};

void meshcallback(const char *event, const char *data)
{
	request.body=data;
	http.post(request,response,headers);
	Serial.println("send");
	Serial.println(response.status);
	Serial.println(request.body); 
}

void setup()
{
	Serial.begin(9600);
	Serial.println(System.deviceID());
	Serial.print("ip: ");
	Serial.println(WiFi.localIP());
	request.ip = IPAddress(192,168,7,31);
	request.port = 8082;
	request.path="/topics/dataavro";
}

void loop()
{
 	Mesh.subscribe("sensorData", meshcallback);
	//char *data= "{\"deviceID\":\"1\",\"timestamp\":\"2020-01-28T20:47:34+01:00\"}";
	//data[strlen(data)]=0; //delete last character ->}
	//data++; //delete first character -> {}
	//char* message = strtok(data, ",");
	//request.body = "{\"value_schema\": \"{\"type\": \"record\", \"name\": \"User\", \"fields\": [{\"name\": \"name\", \"type\": \"string\"}]}\", \"records\": [{\"value\": {\"name\": \"testUser\"}}]}";
	delay(500);
}