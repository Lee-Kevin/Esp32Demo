#include <Wire.h>
#include <SeeedGrayOLED.h>

#include "WiFi.h"

void setup()
{
    Serial.begin(115200);
    
    Wire.begin();
    SeeedGrayOled.init();             //initialize SEEED OLED display
    SeeedGrayOled.clearDisplay();     //Clear Display.
    SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
    SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text
     SeeedGrayOled.setTextXY(0,0);
    SeeedGrayOled.putString("Hello SEEED"); //Print Hello World
    
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
    

      
    // for(char i=0; i < 12 ; i++)
      // {
      // SeeedGrayOled.setTextXY(i,0);  //set Cursor to ith line, 0th column
      // SeeedGrayOled.setGrayLevel(i); //Set Grayscale level. Any number between 0 - 15.
      // SeeedGrayOled.putString("SEEED"); //Print Hello World
      // }    
}

void loop()
{
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        //
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(500);
            //sprintf(buffer,"%d: %s %s",i,WiFi.SSID(i),WiFi.RSSI(i));
            String temp = String(i+1) +":" +WiFi.SSID(i)+WiFi.RSSI(i);
            Serial.println(temp);
            //const char* c_s = temp.c_str();
            const char* c_s = WiFi.SSID(i).c_str();
            //Serial.println(buffer);
            SeeedGrayOled.setTextXY(i,0);  //set Cursor to ith line, 0th column
            SeeedGrayOled.putString(c_s); //Print Hello World
            
            // SeeedGrayOled.putString(WiFi.SSID(i)); //Print Hello World
            // SeeedGrayOled.putString(WiFi.RSSI(i)); //Print Hello World
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(10000);
}


