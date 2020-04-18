/*
 * Project IOTArgon
 * Description:
 * Author:
 * Date:
 */

#include <time.h>
#include "HttpClient.h"

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
	request.ip = IPAddress(192,168,7,31); //ip adress of the rest proxy
	request.port = 8082; //port of the rest proxy
	request.path="/topics/dataavro";
}

void loop()
{
 	Mesh.subscribe("sensorData", meshcallback);
	delay(500);
}