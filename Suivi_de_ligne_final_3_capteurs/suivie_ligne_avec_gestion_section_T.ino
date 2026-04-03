#define IR_SENSOR_RIGHT 12 //pin du capteur droit
#define IR_SENSOR_LEFT 11 // pin du capteur gauche
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

//flag init (à changer selon le point de départ et si l'on souhaite prendre le virage en T)
bool flagPositionDepart = false; //false à gauche, true à droite
bool flagPrendreT = true; //prend le virage en T si true sinon va tout droit

int compteurVirage = 0;//compteur pour la gestion de virage

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

  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  // Combine the two sensor values into a single 2-bit value
  int sensorState = (rightIRSensorValue << 1) | leftIRSensorValue;

  switch (sensorState) {
    case 0b00: // les 2 capteurs ne détecte pas la ligne
      rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
      break;


    case 0b01: // capteurs gauche detecte une ligne noir, droit ne detecte rien
      if(flagPrendreT==true && compteurVirage==2){
        //faire l'action de virage à gauche
        bool passageLigne = true;
        bool tempDetecteLigne = false;
        rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);

        while(passageLigne){//tant que la ligne n'a pas été traversé par le capteur, tourne
          if(digitalRead(IR_SENSOR_LEFT) != 0){
            tempDetecteLigne = true;
          }
          if(digitalRead(IR_SENSOR_LEFT) == 0 && tempDetecteLigne==true){
            passageLigne = false;
          }
        }
        flagPrendreT = false;
        compteurVirage == 0;
      }
      if(flagPositionDepart==true){
        compteurVirage++;
      }
      if(flagPositionDepart==false){
        compteurVirage = 0;
      }
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
      break;


    case 0b10: // capteurs droit detecte une ligne noir, gauche ne detecte rien 
      if(flagPrendreT==true && compteurVirage==2){
        //faire l'action de virage à droite
        bool passageLigne = true;
        bool tempDetecteLigne = false;
        rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);

        while(passageLigne){//tant que la ligne n'a pas été traversé par le capteur, tourne
          if(digitalRead(IR_SENSOR_RIGHT) != 0){
            tempDetecteLigne = true;
          }
          if(digitalRead(IR_SENSOR_RIGHT) == 0 && tempDetecteLigne==true){//une fois la ligne passé, reprendre normalement
            passageLigne = false;
          }
        }
        flagPrendreT = false;
        compteurVirage == 0;

      }
      if(flagPositionDepart==true){
        compteurVirage = 0;
      }
      if(flagPositionDepart==false){
        compteurVirage++;
      }

      rotateMotor(-MOTOR_SPEED, -MOTOR_SPEED);
      break;


    case 0b11: // 2 capteurs detecte une ligne noir
      rotateMotor(0, 0);
      break;

    default:
      rotateMotor(0,0);//il est là par principe lui mais en théorie, il ne sert à rien
      break;
  }

}

/************************************************************/
/* Entrée : 2 int repésentant la vitesse des moteurs        */
/* Sortie : aucun                                           */
/* Description : vérifie si le sens de marche souhaité selon*/
/*  le signe du int entré, change les valeurs des pins en   */
/*  conséquence défini dans le setup puis change la vitesse */
/*  souhaiter du moteur                                     */
/************************************************************/
void rotateMotor(int leftMotorSpeed, int rightMotorSpeed)
{
  
  
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
