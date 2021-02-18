# IOT-temperature
This project is based on the concept of Internet of Things. The goal is to detect the temperature through a DHT22 sensor, which this information will be received by an Android application using BLE (Bluetooth Low Energy). Finally, all the data will be stored in a database in a local Cloud.

(diagrama)

## Android App
It consists of an Android application that connects the sensor with the Cloud, through Bluetooth Low Energy.
(imatge)


## Embedded platform
The circuit in this project is easy.
(imatge)


## How to create the project
### Hardware required
- Visual Studio Code
- Android Studio
- WAMP Server

### Hardware required
- Phone with Android
- Computer
- ESP32 platform, DHT22 sensor and resistor
- Micro-usb cable
- USB type-C (cable required to connect the phone to the computer)

### Load the code inside the embedded platform
Folder: sensor_temperatura
Software: Visual Studio Code
- Connect the circuit to the computer
- Upload the code

### Load the app in the phone
Folder: IOT_app
Software: Android Studio
- Connect the phone to the computer
- Run the code in the device, not in an emulator

### Connection to the Cloud
Folder: sensor_temp
Software: WAMP Server
- Run WAMP Server
- Inside the folder "wamp", there is a folder named "www"
- Inside this folder, insert the folder of this project called "sensor_temp"
- Write "localhost" in a new tab of a browser. It will appear different information. Select "myphpadmin" (this is the database)
- Create a new database called "iot_db". Inside create a new table called "weather" with two columns: "id" (int) and "temp" (int). Note: "id" must have checked the "Auto-Increment" option.

IMPORTANT: The phone and the computer must be connected in the same wi-fi network
-  From the computer, access to the windows configuration
-  Select option "Network and Internet"
-  Select option "Mobile Hotspot"
-  From the phone, connect to the new revealed network

