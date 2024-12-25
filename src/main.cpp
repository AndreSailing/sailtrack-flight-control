#include <Arduino.h>
#include <Encoder.h>

#include <SailtrackModule.h>
#define CHANGE_MODE 0x03
#define FALLING_MODE 0x02

// -------------------------- Configuration -------------------------- //
//pin E6B2-CWZ3E

#define ENCODER_PIN_A 21 //black
#define ENCODER_PIN_B 16 //white
#define ENCODER_PIN_Z 17 // orange

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
    Serial.print(encoderPos);
    Serial.print(" -- ");
    Serial.print(digitalRead(ENCODER_PIN_A));
    Serial.print("  valore pin A   ");
    Serial.print(digitalRead(ENCODER_PIN_B));
    Serial.print("  valore pin B   ");
    Serial.println();

    Serial.print(digitalRead(ENCODER_PIN_Z));
    Serial.print("  valore pin Z   ");
    Serial.println();
  
  
  
  delay(100); // Ritardo ridotto per letture più frequenti
}
void updateEncoder(){
  int stateA = digitalRead(ENCODER_PIN_A);
  int stateB = digitalRead(ENCODER_PIN_B);
  if (stateA==stateB)
  {
   encoderPos++;
  }else{
    encoderPos--;
  }
  
}
void resetEncoder(){

  zIndexDetected=true;
}