#define M1_PWM 5
#define M1_DIR 4
#define M2_PWM 6
#define M2_DIR 7
#define TCR 8   // Capteur de ligne

void setup() {
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(TCR, INPUT);

  Serial.begin(9600);
  Serial.println("Test moteurs + capteur de ligne");
}

void loop() {

  // Lecture du capteur
  bool estNoir = (digitalRead(TCR) == LOW);  

  if (!estNoir) {
    // Marche avant
    digitalWrite(M1_DIR, LOW); 
    digitalWrite(M2_DIR, LOW);

    analogWrite(M1_PWM, 90);  // vitesse moteur 1
    analogWrite(M2_PWM, 90);  // vitesse moteur 2

    Serial.println("Ligne NOIRE détectée -> moteurs ON");
  } 
  else {
    // Arrêt moteurs
    analogWrite(M1_PWM, 0);
    analogWrite(M2_PWM, 0);

    Serial.println("Ligne BLANCHE détectée -> moteurs OFF");
  }

  delay(200); // délai court pour réactivité
}
