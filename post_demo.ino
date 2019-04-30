#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>

#include <ESP8266WiFi.h>

const char* NETWORK_SSID = "elshaarawy";
const char* NETWORK_PASSWORD = "flowbase";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //Serial connection
  WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);   //WiFi connection

  printLns(2);

  waitConnection();
  
  printLns(4);
  
  printIpAddress();
  
  printLns(4);
  
  Serial.println("################### NEW REQUEST ###################");
  simplePostRequest();
  Serial.println("################### END REQUEST ###################");

}

void loop() {
  //  Serial.println("################### NEW REQUEST ###################");
  //  simplePostRequest()
  //  Serial.println("################### END REQUEST ###################");
  //  Serial.println();
  //
  //  delay(3000);
}

void waitConnection() {

  Serial.print("Connecting to: ");
  Serial.print(NETWORK_SSID);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(300);
    Serial.print(" .");
  }
  Serial.println();
  Serial.println("Connected!");
  Serial.println();
  delay(2000);

}


void printIpAddress() {
  Serial.println("###################################################");
  Serial.println();

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println();
  Serial.println("###################################################");
  Serial.println();

  delay(2000);
}

void simplePostRequest() {
  String response = post();
  Serial.print("Response: ");
  Serial.println(response);
  Serial.print("Post ID: ");
  Serial.println(deserializeResponseId(response));
}

String  post() {
  // declare http object
  HTTPClient http;

  // begain the setup url
  http.begin("http://jsonplaceholder.typicode.com/posts");

  http.addHeader("Content-Type", "application/json; charset=UTF-8");

  String body = serializePostBody("test title", "test body", 55);

  Serial.println("Body: " + body);
  int code = http.POST(body);
  Serial.print("Status Code: ");
  Serial.println (code);

  String payload = http.getString();
  http.end();
  return payload;
}









String serializePostBody(String postTitle, String postBody, int userId) {

  DynamicJsonDocument doc(74);

  doc["title"] = postTitle;
  doc["body"] = postBody;
  doc["userId"] = userId;
  String output;
  serializeJson(doc, output);
  //  serializeJsonPretty(doc, output);
  return output;
}














String deserializeResponseId(String response) {

  DynamicJsonDocument doc(106);
  DeserializationError error = deserializeJson(doc, response);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    return error.c_str();
  }

  return doc["id"];

}

void printLns(int lines) {
  for (int i = 0; i < lines; i++) {
    Serial.println();
  }
}
