#include <Wire.h>
#include <VL53L0X.h>

VL53L0X capteur;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!capteur.init()) {
    Serial.println("Erreur capteur");
    while (1);
  }

  capteur.startContinuous();
}

void loop() {

  int distance = capteur.readRangeContinuousMillimeters();

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" mm");

  if(distance <= 100){
    Serial.println("Obstacle detecte");
  }
  else{
    Serial.println("Pas d obstacle");
  }

  delay(500);
}