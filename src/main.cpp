#include <Arduino.h>
#include <Encoder.h>

#include <SailtrackModule.h>
#define CHANGE_MODE 0x03
#define FALLING_MODE 0x02

// -------------------------- Configuration -------------------------- //
//pin E6B2-CWZ3E

#define ENCODER_PIN_A 21 //black
#define ENCODER_PIN_B 27 //white
#define ENCODER_PIN_Z 25 // orange

// ------------------------------------------------------------------- //
volatile long encoderPos=0;
volatile bool zIndexDetected=false;
void updateEncoder();
void resetEncoder();

void setup() {
  
  pinMode(ENCODER_PIN_A, INPUT);
  pinMode(ENCODER_PIN_B, INPUT);
  pinMode(ENCODER_PIN_Z, INPUT_PULLUP); // Configurazione del pin Z come input con pull-up
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A),updateEncoder,CHANGE_MODE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_Z),resetEncoder,FALLING_MODE);
  Serial.begin(115200); // Inizializzazione della comunicazione seriale
}

void loop() {
  if (zIndexDetected)
  {
    Serial.print("reset position");
  }else{
    Serial.print(encoderPos);
    Serial.print(digitalRead(ENCODER_PIN_A));
    Serial.print("  valore pin A   ");
    Serial.print(digitalRead(ENCODER_PIN_B));
    Serial.print("  valore pin B   ");
    Serial.println();
  }
  
  
  delay(100); // Ritardo ridotto per letture più frequenti
}
void updateEncoder(){
  int stateA = digitalRead(ENCODER_PIN_A);
  int stateB = digitalRead(ENCODER_PIN_B);
  Serial.print("state A ");
  Serial.print(stateA);
  Serial.println("state B ");
  Serial.print(stateB);
  Serial.println();
  if (stateA==stateB)
  {
   encoderPos++;
  }else{
    encoderPos--;
  }
  
}
void resetEncoder(){
  encoderPos=0;
  zIndexDetected=true;
}/*
#include <Arduino.h>
#include <Encoder.h>

// -------------------------- Configuration -------------------------- //
// Pin E6B2-CWZ3E
#define ENCODER_PIN_A 27 // Pin A dell'encoder
#define ENCODER_PIN_B 21 // Pin B dell'encoder
#define ENCODER_PIN_Z 25 // Pin Z dell'encoder

// Creazione dell'oggetto Encoder
Encoder myEncoder(ENCODER_PIN_A, ENCODER_PIN_B);

long oldPosition  = -999;
long newPosition;

void setup() {
  Serial.begin(9600); // Inizializzazione della comunicazione seriale
  pinMode(ENCODER_PIN_Z, INPUT_PULLUP); // Configurazione del pin Z come input con pull-up
}

void loop() {
  newPosition = myEncoder.read(); // Lettura della posizione dell'encoder

  if (newPosition != oldPosition) { // Se la posizione è cambiata
    Serial.print("Posizione: ");
    Serial.println(newPosition); // Stampa la nuova posizione
    oldPosition = newPosition;
  }

  // Gestione del segnale Z (indice)
  if (digitalRead(ENCODER_PIN_Z) == LOW) {
    Serial.println("Segnale Z rilevato!");
    myEncoder.write(0); // Resetta la posizione dell'encoder
  }

  delay(100); // Ritardo per evitare letture troppo frequenti
}*/

