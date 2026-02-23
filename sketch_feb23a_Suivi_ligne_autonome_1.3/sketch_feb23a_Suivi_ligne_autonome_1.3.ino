// ============================
// CAPTEURS IR
// ============================
#define IR_SENSOR_RIGHT 8
#define IR_SENSOR_LEFT  9

// ============================
// PARAMÈTRES
// ============================
#define MOTOR_SPEED 180
#define DIRECTION 2   // 0 = tout droit, 1 = gauche, 2 = droite
#define BLACK_COUNT_MAX 20 // seuil intersection (à régler)

// ============================
// VARIABLES
// ============================
int blackCounter = 0;
bool intersectionDejaPasse = false;

// ============================
// MOTEURS
// ============================
#define LEFT_MOTOR_PWM 5
#define LEFT_MOTOR_DIR 4
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

  // ============================
  // SUIVI DE LIGNE NORMAL
  // ============================
  if (rightIR == LOW && leftIR == LOW)
  {
    blackCounter = 0;
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  else if (rightIR == HIGH && leftIR == LOW)
  {
    blackCounter = 0;
    rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
  }
  else if (rightIR == LOW && leftIR == HIGH)
  {
    blackCounter = 0;
    rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
  }

  // ============================
  // LES DEUX CAPTEURS VOIENT NOIR
  // ============================
  else
  {
    blackCounter++;

    // Noir bref → virage (on continue tout droit)
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);

    // Noir prolongé → intersection
    if (blackCounter > BLACK_COUNT_MAX)
    {
      if (!intersectionDejaPasse)
      {
        intersectionDejaPasse = true;
        executerDirection();
      }
      else
      {
        stopMotors();
        while (1);
      }
    }
  }

  delay(5); // stabilisation capteurs (TRÈS IMPORTANT)
}

// ============================
// DIRECTION À L’INTERSECTION
// ============================
void executerDirection()
{
  if (DIRECTION == 0)
  {
    // Avance très courte
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    delay(120);

    // Recentre sur la ligne
    while (digitalRead(IR_SENSOR_LEFT) == HIGH ||
           digitalRead(IR_SENSOR_RIGHT) == HIGH)
    {
      if (digitalRead(IR_SENSOR_LEFT) == HIGH)
        rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);   // corrige à gauche
      else if (digitalRead(IR_SENSOR_RIGHT) == HIGH)
        rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);   // corrige à droite
    }
  }

  else if (DIRECTION == 1)
  {
    rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
    delay(350);
  }

  else if (DIRECTION == 2)
  {
    rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
    delay(350);
  }
}

// ============================
// MOTEURS
// ============================
void rotateMotor(int rightSpeed, int leftSpeed)
{
  digitalWrite(RIGHT_MOTOR_DIR, rightSpeed > 0 ? HIGH : LOW);
  digitalWrite(LEFT_MOTOR_DIR,  leftSpeed  > 0 ? HIGH : LOW);

  analogWrite(RIGHT_MOTOR_PWM, abs(rightSpeed));
  analogWrite(LEFT_MOTOR_PWM,  abs(leftSpeed));
}

void stopMotors()
{
  analogWrite(RIGHT_MOTOR_PWM, 0);
  analogWrite(LEFT_MOTOR_PWM, 0);
}

