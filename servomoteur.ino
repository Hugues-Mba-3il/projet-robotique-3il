#include "Freenove_WS2812_Lib_for_ESP32.h" 
#include <SPI.h> 
#include <TFT_eSPI.h> 
#include <WiFi.h> 

#define TFT_GREY  0x5AEB 
#define LEDS_PIN 48 

TFT_eSPI tft = TFT_eSPI(); 
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(1, LEDS_PIN, 0, TYPE_GRB);
char ssid[] = "TP-Link_F99E"; 
char pass[] = "05186150";  

int compt = 0; 

String IPtoString(IPAddress& ip){
  String ips;
  ips.reserve(16);
  ips = ip[0]; ips+=':';
  ips += ip[1]; ips+=':';
  ips += ip[2]; ips+=':';
  ips += ip[3];
  return ips; 

}

void setup() {
  Serial.begin(9600);
  
  strip.begin(); 
  strip.setBrightness(10); 
  
  tft.init(); 
  tft.setRotation(0); 
  tft.fillScreen(TFT_GREY); 
  tft.setTextColor(TFT_WHITE, TFT_GREY); 
  tft.drawString("Affichage OK", 0, 20, 4); 
  

  Serial.println("FIN FONCTION SETUP");

  WiFi.begin(ssid, pass); 
  WiFi.setSleep(false); 
  while (WiFi.status() != WL_CONNECTED) { 
      delay(500); 
      Serial.println(".."); 
      Serial.println("WIFI connecté"); 
      Serial.println(WiFi.localIP());
      tft.drawString("WIFI connecté", 0, 50, 4); 
      IPAddress ip = WiFi.localIP();
      String ipString = IPtoString(ip);
      tft.drawString("IP : " + ipString, 0, 80, 4);

     
    } 

}


void loop() {
  
  compt ++;

  
  tft.drawString("Compteur : " + String(compt), 0, 110, 4);

  //Serial.print("Nombre de passages : ");
  //Serial.println(compt);


  // Rouge
  strip.setLedColorData(0, 255, 0, 0);
  strip.show();
  delay(1000);

  // Éteint
  strip.setLedColorData(0, 0, 0, 0);
  strip.show();
  delay(1000);
}

