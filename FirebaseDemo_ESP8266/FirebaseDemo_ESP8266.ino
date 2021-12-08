#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
                          
#define FIREBASE_HOST "esp8266-23cf9-default-rtdb.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "UIcaQxV0q1u7jaRHQ6bZ6A2FlPVFyQ5t6r7nGZQd" //Your Firebase Database Secret goes here

#define WIFI_SSID "GPU 4G"                                               //WiFi SSID to which you want NodeMCU to connect
#define WIFI_PASSWORD "shogun@123"                                      //Password of your wifi network 
#include "DHT.h"

#define DHTPIN D2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
  

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

// Declare global variable to store value
int val=0;



void setup() {

  Serial.begin(115200);                                   // Select the same baud rate if you want to see the datas on Serial Monitor
   dht.begin();
  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase

  Firebase.reconnectWiFi(true);
  delay(1000);



  
}

void loop() { 

// Firebase Error Handling And Writing Data At Specifed Path************************************************
float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
float h1 = analogRead(A0);
if (Firebase.setFloat(firebaseData, "/Gas Sensor", h1/1024*100)) {    // On successful Write operation, function returns 1  
               Serial.println("Value Uploaded Successfully");
               Serial.print("Val = ");
               Serial.println(h1/1024*100);
               Serial.println("\n");
               delay(1000);

     }
     
     if (Firebase.setFloat(firebaseData, "/Temperature",t)) {    // On successful Write operation, function returns 1  
               Serial.println("Value Uploaded Successfully");
               Serial.print("Val = ");
               Serial.println(t);
               Serial.println("\n");
      
           
     }


     
     

else {        
    Serial.println(firebaseData.errorReason());
  }

}
