#define M1_PWM 5
#define M1_DIR 4
#define M2_PWM 6
#define M2_DIR 7
const int capteurPin = A0;


void setup() {
  // Capteur distance
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);

  // Serial
  Serial.begin(9600);
  Serial.println(F("Test detecteur d'obstacle"));
}

void loop() {
  int valeur = analogRead(capteurPin);

  Serial.print("Valeur : ");
  Serial.println(valeur);

  if (valeur > 400) {
    Serial.println("Obstacle detecte");
    analogWrite(M1_PWM, 0);  // vitesse moteur 1
    analogWrite(M2_PWM, 0);
    delay(500);
  } else {
    Serial.println("Pas d'obstacle");
    digitalWrite(M1_DIR, LOW); 
    digitalWrite(M2_DIR, LOW);

    analogWrite(M1_PWM, 120);  // vitesse moteur 1
    analogWrite(M2_PWM, 120);
    delay(500);
  }

  delay(100);
}
