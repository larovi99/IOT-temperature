
#include "DHT.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
//#include <iostream>
#include <string>

#define DHTPIN 26     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

BLECharacteristic *pCharacteristic;
 
bool deviceConnected = false;

#define SERVICE_UUID           "19B10000-E8F2-537E-4F6C-D104768A1214" // UART service UUID
#define CHARACTERISTIC_UUID_RX "19B10000-E8F2-537E-4F6C-D104768A1214"
#define DHTDATA_CHAR_UUID "19B10000-E8F2-537E-4F6C-D104768A1214" 
 
 
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
 
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};
 
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      Serial.println(rxValue[0]);
 
      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
 
        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();
        Serial.println("*********");
      }
 
      
    }
};



void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 test!"));
  dht.begin();

  // Create the BLE Device
  BLEDevice::init("ESP32 DHT22"); // Give it a name
 
  //Configure device as Server BLE
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
 
  // Create an UART Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  //Create a characteristic BLE to send data
  pCharacteristic = pService->createCharacteristic(
                      DHTDATA_CHAR_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                       
  pCharacteristic->addDescriptor(new BLE2902());
 
 
  // Create a characteristic BLE to send data
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
 
  pCharacteristic->setCallbacks(new MyCallbacks());
 
  // Start a service
  pService->start();
 
  // ESP32 discovery starts
  pServer->getAdvertising()->start();
  Serial.println("Waiting for a device...");
}

void loop() {
  if(deviceConnected){
      // Wait a few seconds between measurements.
    

    // Reading temperature or humidity takes about 250 milliseconds!
    // Read temperature as Celsius (the default)
    int t = dht.readTemperature();


    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    else{
      Serial.print(F("Temperature: "));
      Serial.print(t);
      Serial.print('\n');
    }

    

    char dhtDataString[16];
    sprintf(dhtDataString, "%d", t);

    pCharacteristic->setValue(dhtDataString);
   
     
    pCharacteristic->notify(); // Send data to the app
    Serial.print("*** Send data: ");
    Serial.print(dhtDataString);
    Serial.println(" ***");

  }
  
  //wait 10 seconds
  delay(10000);

}
