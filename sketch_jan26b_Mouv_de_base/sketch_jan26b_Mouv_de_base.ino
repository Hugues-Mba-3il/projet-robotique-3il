#define M1_PWM 5
#define M1_DIR 4


#define M2_PWM 6
#define M2_DIR 7

void avancer(int vitesse) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  analogWrite(M1_PWM, vitesse);
  analogWrite(M2_PWM, vitesse);
}

void reculer(int vitesse) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  analogWrite(M1_PWM, vitesse);
  analogWrite(M2_PWM, vitesse);
}

void tournerGauche(int vitesse) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, HIGH);
  analogWrite(M1_PWM, vitesse);
  analogWrite(M2_PWM, vitesse);
}

void tournerDroite(int vitesse) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, LOW);
  analogWrite(M1_PWM, vitesse);
  analogWrite(M2_PWM, vitesse);
}

void arreter(){
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
}
}
