#define IR_SENSOR_RIGHT 12 //pin du capteur droit
#define IR_SENSOR_LEFT 11 // pin du capteur gauche
#define IR_SENSOR_MIDDLE 13// pin du capteur centrale
#define MOTOR_SPEED 220

//Right motor
int enableRightMotor=6; // contrôle la vitesse du moteur via PWM
// les pins suivantes contrôles le sens de rotation du moteur, l'une doit toujours être à LOW et l'autre HIGH sauf pour l'arrêt
int rightMotorPin1=7; // HIGH pour la marche avant, LOW pour marche arrière
int rightMotorPin2=8; // LOW pour marche avant et HIGH pour marche arrière

//Left motor
int enableLeftMotor=5; // contrôle la vitesse du moteur via PWM
// les pins suivantes contrôles le sens de rotation du moteur, l'une doit toujours être à LOW et l'autre HIGH sauf pour l'arrêt
int leftMotorPin1=9; // HIGH pour la marche avant, LOW pour marche arrière
int leftMotorPin2=10; // LOW pour marche avant et HIGH pour marche arrière


///////////////////////////////////A ADAPTER AU POINT DE DEPART ET AU TRAJET VOULUT/////////////////////////////////////////////////
bool flagPrendreT = true; //prend le virage en T si true sinon va tout droit
bool flagPositionDepart = false; //false à gauche, true à droite

void setup()
{
  TCCR0B = (TCCR0B & 0xF8) | 0x01; //modifie la fréquence du signal PWM
  
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);   

}


void loop()
{

  int sensorState = SensorState();//lecture des capteurs de ligne

  switch (sensorState) {
    case 0b000: // Aucun capteur ne détecte la ligne
    case 0b010: // Seul le capteur central détecte la ligne
      rotateMotor(MOTOR_SPEED, MOTOR_SPEED); // Avancer tout droit
      break;

    case 0b001: // Seul le capteur gauche détecte la ligne
    case 0b011: // Gauche et central détectent la ligne
      rotateMotor(-MOTOR_SPEED/2, MOTOR_SPEED); // Tourner légèrement à gauche
      break;

    case 0b100: // Seul le capteur droit détecte la ligne
    case 0b110: // Droit et central détectent la ligne
      rotateMotor(MOTOR_SPEED, -MOTOR_SPEED/2); // Tourner légèrement à droite
      break;

    case 0b101: // Droit et gauche détectent la ligne (gérer le virage en T)
      bool retourSurUneLigne = false;
        while(retourSurUneLigne==false){//tant qu'une ligne n'a pas été reprise pour le suivi
          if((flagPositionDepart==false) && (flagPrendreT==true)){ //départ à gauche, prise du virage en T
            //tourne à droite jusqu'à trouver la ligne
            while(SensorState()!=0b010){
              rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
            }
            retourSurUneLigne = true;

          }
          else if((flagPositionDepart==true) && (flagPrendreT==true)){ //départ à droite, prise du virage en T
            //tourne à gauche jusqu'à trouver la ligne
            while(SensorState()!=0b010){
              rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
            }
            retourSurUneLigne = true;
          }
          else if((flagPositionDepart==false) && (flagPrendreT==false)){ //départ à droite, continue tout droit
            //tourne à droite jusqu'à trouver la ligne
            while(SensorState()!=0b010){
              rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
            }
            retourSurUneLigne = true;
          }
          else{ //départ à droite, continue tout droit
            //tourne à gauche jusqu'à trouver la ligne
            while(SensorState()!=0b010){
              rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
            }
            retourSurUneLigne = true;
          }
        }
      break;

    case 0b111: // Tous les capteurs détectent la ligne
      rotateMotor(0, 0); // Arrêter le robot
      delay(100);
      break;

    default:
      rotateMotor(0, 0); // Cas par défaut (ne devrait jamais arriver)
      break;
  
  }
}


/************************************************************/
/* Entrée : aucun                                           */
/* Sortie : un int représentant l'état des capteurs         */
/* Description : lis les capteurs infrarouge de ligne       */
/*  et retourne le résultat en une seule variable           */
/************************************************************/
int SensorState(){
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);
  int middleIRSensorValue = digitalRead(IR_SENSOR_MIDDLE);

  // combine les trois valeurs des capteurs en une seule (désolé, j'ai inversé la gauche et la droite...oups ¯\(ツ)/¯)
  return ((rightIRSensorValue << 2) | (middleIRSensorValue << 1) | leftIRSensorValue);
}


/************************************************************/
/* Entrée : 2 int repésentant la vitesse des moteurs        */
/* Sortie : aucun                                           */
/* Description : vérifie si le sens de marche souhaité selon*/
/*  le signe du int entré, change les valeurs des pins en   */
/*  conséquence défini dans le setup puis change la vitesse */
/*  souhaiter du moteur                                     */
/************************************************************/
void rotateMotor(int leftMotorSpeed, int rightMotorSpeed){
    
  if (rightMotorSpeed < 0) // marche arrière moteur droit
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0) //marche avant moteur droit
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else //arrêt
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0) // marche arrière moteur gauche
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0) // marche avant moteur droit
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else //arrêt
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
