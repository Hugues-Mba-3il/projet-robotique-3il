#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>

VL53L0X capteur;
Servo monServo;

int angle = 0;        // position actuelle
int sens = 1;         // direction (1 ou -1)

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!capteur.init()) {
    Serial.println("Erreur capteur");
    while (1);
  }

  capteur.startContinuous();
  monServo.attach(9);
}

void loop() {

  int distance = capteur.readRangeContinuousMillimeters();

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" mm");

  //🚨 Si obstacle → STOP
  if(distance <= 100){
    Serial.println("Obstacle detecte → STOP");
     on ne change plus l’angle → servo figé
  }
  else{
    Serial.println("Pas d obstacle → rotation");

     rotation continue
    angle += sens;

    // changement de sens aux limites
    if(angle >= 150){
      sens = -1;
    }
    if(angle <= 50){
      sens = 1;
    }

    monServo.write(angle);
    delay(20); // vitesse rotation
  }
}