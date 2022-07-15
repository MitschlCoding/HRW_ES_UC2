#include <WiFi.h>
#include <HTTPSServer.hpp>
//provides a way to create certificats
#include <SSLCert.hpp>
//work with http requests and response
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
//Json parsing and serialisation
#include <ArduinoJson.h>
//file system
#include <SPIFFS.h>
//System for IODevices
#include "IOController.h"
#include "LED.h"
#include "MotorULN2003.h"
#include "MotorDRV8825.h"

using namespace httpsserver;

const char* ssid = "Modular-UC2";
const char* password = "1234567890";

//initialise a sertificate and an https server
SSLCert* cert;
HTTPSServer* secureServer;

//initialise the IOController
uc2::IOController* ioContrTest;

void setup(){
  //setup serial connection
  Serial.begin(115200);
  //test if file system works
  if(!SPIFFS.begin()){
    Serial.println("Error with SPIFFS");
    return;
  }

  //create a certificate and test if it works
  Serial.println("Create Cert");
  cert = new SSLCert();
  int createCertResult = createSelfSignedCert(*cert, KEYSIZE_2048, "CN=espmicorscope, O=aaa_hrw, C=GER");
  if(createCertResult != 0){
    Serial.println("Error generating certificate");
    return;
  }

  //create a new HTTPSServer with the created certificate
  secureServer = new HTTPSServer(cert);

  //start the access Point and print the IP
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());

  //create a resource node, that waits for a HTTP GET for the index page and returns the index page
  ResourceNode* nodeIndex = new ResourceNode("/", "GET", [](HTTPRequest* req, HTTPResponse* res){
    File indexFile = SPIFFS.open("/index.html", "r");
    if(indexFile){
      res->print(indexFile.readString());
      indexFile.close();
    }
  });

  //resource node, that handels the style.css
  ResourceNode* nodeCss = new ResourceNode("/style.css", "GET", [](HTTPRequest* req, HTTPResponse* res){
    File styleFile = SPIFFS.open("/style.css", "r");
    if(styleFile){
      res->print(styleFile.readString());
      styleFile.close();
    }
  });

  //resource node, that handels the index.js
  ResourceNode* nodeJS = new ResourceNode("/index.js", "GET", [](HTTPRequest* req, HTTPResponse* res){
    File jsFile = SPIFFS.open("/index.js", "r");
    if(jsFile){
      res->print(jsFile.readString());
      jsFile.close();
    }
  });

  //resource node, for a POST request, to add an LED
  ResourceNode* nodeAddLED = new ResourceNode("/post/add/LED", "POST", [](HTTPRequest* req, HTTPResponse* res){
    size_t bodyLength = req->getContentLength();
    char* buff = new char[bodyLength+1];
    buff[bodyLength] = '\0';
    req->readChars(buff, bodyLength);
    int id;
    int pin;
    id = atoi(buff);
    char* ptr = strtok(buff, ",");
    ptr = strtok(NULL, ",");
    pin = atoi(ptr);
    ioContrTest->addODevice(new uc2::LED(id, pin));
    //init device
    ioContrTest->getODevice(id)->deviceInit();
    delete buff;
  });

  ResourceNode* nodeChangeLEDState = new ResourceNode("/post/change/LED", "POST", [](HTTPRequest* req, HTTPResponse* res){
    size_t bodyLength = req->getContentLength();
    char* buff = new char[bodyLength+1];
    buff[bodyLength] = '\0';
    req->readChars(buff, bodyLength);
    StaticJsonDocument<200> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, buff);
    if(error){
      Serial.println(error.f_str());
      return;
    }
    int id = jsonDoc["id"];
    uc2::LED* ledTemp = (uc2::LED*)ioContrTest->getODevice(id);
    ledTemp->turnOnOff();
    delete buff;
  });

  //resource node, for a POST request, to add a Motor
  ResourceNode* nodeAddMotorULN2003 = new ResourceNode("/post/add/Motor/ULN2003", "POST", [](HTTPRequest* req, HTTPResponse* res){
    size_t bodyLength = req->getContentLength();
    char* buff = new char[bodyLength+1];
    buff[bodyLength] = '\0';
    req->readChars(buff, bodyLength);
    int id;
    int* pins = new int[4];
    //set id
    id = atoi(buff);
    //go through all elements in the string with a string token and push them into pins
    char* ptr = strtok(buff, ",");
    for(size_t i = 0; i < 4; i++){
      ptr = strtok(NULL, ",");
      pins[i] = atoi(ptr);
    }
    ioContrTest->addODevice(new uc2::MotorULN2003(id, pins[0], pins[1], pins[2], pins[3]));
    //init device
    ioContrTest->getODevice(id)->deviceInit();
    delete buff;
    delete pins;
  });

  ResourceNode* nodeChangeMotorStateULN2003 = new ResourceNode("/post/change/Motor/ULN2003", "POST", [](HTTPRequest* req, HTTPResponse* res){
    size_t bodyLength = req->getContentLength();
    char* buff = new char[bodyLength+1];
    buff[bodyLength] = '\0';
    req->readChars(buff, bodyLength);
    StaticJsonDocument<200> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, buff);
    if(error){
      Serial.println(error.f_str());
      return;
    }
    int id = jsonDoc["id"];
    int steps = jsonDoc["steps"];
    uc2::MotorULN2003* motorTemp = (uc2::MotorULN2003*)ioContrTest->getODevice(id);
    motorTemp->steps = steps;
    delete buff;
  });

  //resource node, for a POST request, to add a Motor
  ResourceNode* nodeAddMotorDRV8825 = new ResourceNode("/post/add/Motor/DRV8825", "POST", [](HTTPRequest* req, HTTPResponse* res){
    size_t bodyLength = req->getContentLength();
    char* buff = new char[bodyLength+1];
    buff[bodyLength] = '\0';
    req->readChars(buff, bodyLength);
    int id;
    int* pins = new int[2];
    //set id
    id = atoi(buff);
    //go through all elements in the string with a string token and push them into pins
    char* ptr = strtok(buff, ",");
    for(size_t i = 0; i < 2; i++){
      ptr = strtok(NULL, ",");
      pins[i] = atoi(ptr);
    }
    ioContrTest->addODevice(new uc2::MotorDRV8825(id, pins[0], pins[1]));
    //init device
    ioContrTest->getODevice(id)->deviceInit();
    delete buff;
    delete pins;
  });

  ResourceNode* nodeChangeMotorStateDRV8825 = new ResourceNode("/post/change/Motor/DRV8825", "POST", [](HTTPRequest* req, HTTPResponse* res){
    size_t bodyLength = req->getContentLength();
    char* buff = new char[bodyLength+1];
    buff[bodyLength] = '\0';
    req->readChars(buff, bodyLength);
    char* ptr = strtok(buff, ",");
    int id = atoi(buff);
    ptr = strtok(NULL, ",");
    int _steps = atoi(ptr);
    uc2::MotorDRV8825* motorTemp = (uc2::MotorDRV8825*)ioContrTest->getODevice(id);
    motorTemp->steps = _steps;
    delete buff;
  });

  ResourceNode* nodeDeleteDevice = new ResourceNode("/post/delete", "POST", [](HTTPRequest* req, HTTPResponse* res){
    size_t bodyLength = req->getContentLength();
    char* buff = new char[bodyLength+1];
    buff[bodyLength] = '\0';
    req->readChars(buff, bodyLength);
    int id;
    id = atoi(buff);
    ioContrTest->removeODevice(id);
    delete buff;
  });

  ResourceNode* nodeGetDevices = new ResourceNode("/get/devices", "GET", [](HTTPRequest* req, HTTPResponse* res){
    DynamicJsonDocument doc(1024);
    String jsonDevices = "{\"devices\": [";
    bool first = true;
    for(auto i: ioContrTest->oDevices){
      if(!first){
        jsonDevices += ",";
      } else {
        first = false;
      }
      jsonDevices += "{\"id\":" + String(i->id) + ", \"type\":\"" + i->type + "\"}";
    }
    jsonDevices += "]}";
    res->print(jsonDevices);
  });

  //initialise node for server, start the server and test if its running
  secureServer->registerNode(nodeIndex);
  secureServer->registerNode(nodeCss);
  secureServer->registerNode(nodeJS);
  secureServer->registerNode(nodeAddLED);
  secureServer->registerNode(nodeChangeLEDState);
  secureServer->registerNode(nodeAddMotorULN2003);
  secureServer->registerNode(nodeChangeMotorStateULN2003);
  secureServer->registerNode(nodeAddMotorDRV8825);
  secureServer->registerNode(nodeChangeMotorStateDRV8825);
  secureServer->registerNode(nodeDeleteDevice);
  secureServer->registerNode(nodeGetDevices);
  secureServer->start();
  if(secureServer->isRunning()){
    Serial.println("Ready");
  }

  //initialises the IOController
  ioContrTest = new uc2::IOController();
  //runs the initialise methods
  ioContrTest->controllerInit();
}

void loop(){
  //run the serverloop every 10 ms
  secureServer->loop();
  //updates the state of all devices every loop
  ioContrTest->controllerUpdate();
  delay(10);
}
