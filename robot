// ============================
// CAPTEURS IR
// ============================
#define IR_SENSOR_RIGHT 8
#define IR_SENSOR_LEFT  9

// ============================
// PARAMÈTRES
// ============================
#define MOTOR_SPEED 180
#define DIRECTION 1   // 0 = tout droit, 1 = gauche, 2 = droite

// ============================
// VARIABLES
// ============================
bool intersectionDejaPasse = false;

// ============================
// MOTEURS (2 roues par côté)
// ============================

// Côté gauche
#define LEFT_MOTOR_PWM 5
#define LEFT_MOTOR_DIR 4

// Côté droit
#define RIGHT_MOTOR_PWM 6
#define RIGHT_MOTOR_DIR 7

void setup()
{// ============================
// CAPTEURS IR
// ============================
#define IR_SENSOR_RIGHT 8
#define IR_SENSOR_LEFT  9

// ============================
// PARAMÈTRES
// ============================
#define MOTOR_SPEED 180
#define DIRECTION 1   // 0 = tout droit, 1 = gauche, 2 = droite

// ============================
// VARIABLES
// ============================
bool intersectionDejaPasse = false;

// ============================
// MOTEURS (2 roues par côté)
// ============================

// Côté gauche
#define LEFT_MOTOR_PWM 5
#define LEFT_MOTOR_DIR 4

// Côté droit
#define RIGHT_MOTOR_PWM 6
#define RIGHT_MOTOR_DIR 7

void setup()
{
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  stopMotors();
}

void loop()
{
  int rightIR = digitalRead(IR_SENSOR_RIGHT);
  int leftIR  = digitalRead(IR_SENSOR_LEFT);

  // Ligne au centre → tout droit
  if (rightIR == LOW && leftIR == LOW)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  // Ligne à droite → tourner à droite
  else if (rightIR == HIGH && leftIR == LOW)
  {
    rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
  }
  // Ligne à gauche → tourner à gauche
  else if (rightIR == LOW && leftIR == HIGH)
  {
    rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
  }
  // Les deux capteurs voient noir
  else
  {
    if (!intersectionDejaPasse)
    {
      intersectionDejaPasse = true;

      delay(100);  // évite double détection

      // Effectuer la direction choisie
      if (DIRECTION == 0)
      {
        rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
        delay(300);
      }
      else if (DIRECTION == 1)
      {
        rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
        delay(300);
      }
      else if (DIRECTION == 2)
      {
        rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
        delay(300);
      }
    }
    else
    {
      // Deuxième fois → STOP définitif
      stopMotors();
      while (1);  // bloque le programme
    }
  }
}

// ============================
// FONCTIONS MOTEURS
// ============================

void rotateMotor(int rightSpeed, int leftSpeed)
{
  // ----- MOTEUR DROIT -----
  if (rightSpeed > 0)
    digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  else if (rightSpeed < 0)
    digitalWrite(RIGHT_MOTOR_DIR, LOW);

  analogWrite(RIGHT_MOTOR_PWM, abs(rightSpeed));

  // ----- MOTEUR GAUCHE -----
  if (leftSpeed > 0)
    digitalWrite(LEFT_MOTOR_DIR, HIGH);
  else if (leftSpeed < 0)
    digitalWrite(LEFT_MOTOR_DIR, LOW);

  analogWrite(LEFT_MOTOR_PWM, abs(leftSpeed));
}

void stopMotors()
{
  analogWrite(RIGHT_MOTOR_PWM, 0);
  analogWrite(LEFT_MOTOR_PWM, 0);
}

  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  stopMotors();
}

void loop()
{
  int rightIR = digitalRead(IR_SENSOR_RIGHT);
  int leftIR  = digitalRead(IR_SENSOR_LEFT);

  // Ligne au centre → tout droit
  if (rightIR == LOW && leftIR == LOW)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  // Ligne à droite → tourner à droite
  else if (rightIR == HIGH && leftIR == LOW)
  {
    rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
  }
  // Ligne à gauche → tourner à gauche
  else if (rightIR == LOW && leftIR == HIGH)
  {
    rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
  }
  // Les deux capteurs voient noir
  else
  {
    if (!intersectionDejaPasse)
    {
      intersectionDejaPasse = true;

      delay(100);  // évite double détection

      // Effectuer la direction choisie
      if (DIRECTION == 0)
      {
        rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
        delay(300);
      }
      else if (DIRECTION == 1)
      {
        rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
        delay(300);
      }
      else if (DIRECTION == 2)
      {
        rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
        delay(300);
      }
    }
    else
    {
      // Deuxième fois → STOP définitif
      stopMotors();
      while (1);  // bloque le programme
    }
  }
}

// ============================
// FONCTIONS MOTEURS
// ============================

void rotateMotor(int rightSpeed, int leftSpeed)
{
  // ----- MOTEUR DROIT -----
  if (rightSpeed > 0)
    digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  else if (rightSpeed < 0)
    digitalWrite(RIGHT_MOTOR_DIR, LOW);

  analogWrite(RIGHT_MOTOR_PWM, abs(rightSpeed));

  // ----- MOTEUR GAUCHE -----
  if (leftSpeed > 0)
    digitalWrite(LEFT_MOTOR_DIR, HIGH);
  else if (leftSpeed < 0)
    digitalWrite(LEFT_MOTOR_DIR, LOW);

  analogWrite(LEFT_MOTOR_PWM, abs(leftSpeed));
}

void stopMotors()
{
  analogWrite(RIGHT_MOTOR_PWM, 0);
  analogWrite(LEFT_MOTOR_PWM, 0);
}
