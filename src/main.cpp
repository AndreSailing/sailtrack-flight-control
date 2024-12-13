#include <Arduino.h>
#include <SailtrackModule.h>
#include <Encoder.h>

// -------------------------- Configuration -------------------------- //
//pin E6B2-CWZ3E
#define ENCODER_PIN_A 21
#define ENCODER_PIN_B 17 
#define ENCODER_PIN_Z 16

#define BATTERY_ADC_PIN 			35
#define BATTERY_ADC_RESOLUTION 		4095
#define BATTERY_ADC_REF_VOLTAGE 	1.1
#define BATTERY_ESP32_REF_VOLTAGE	3.3
#define BATTERY_NUM_READINGS 		32
#define BATTERY_READING_DELAY_MS	20

// ------------------------------------------------------------------- //

SailtrackModule stm;

class ModuleCallbacks: public SailtrackModuleCallbacks {
	void onStatusPublish(JsonObject status) {
		JsonObject battery = status.createNestedObject("battery");
		float avg = 0;
		for (int i = 0; i < BATTERY_NUM_READINGS; i++) {
			avg += analogRead(BATTERY_ADC_PIN) / BATTERY_NUM_READINGS;
			delay(BATTERY_READING_DELAY_MS);
		}
		battery["voltage"] = 2 * avg / BATTERY_ADC_RESOLUTION * BATTERY_ESP32_REF_VOLTAGE * BATTERY_ADC_REF_VOLTAGE;
	}
};

Encoder myEncoder(ENCODER_PIN_A, ENCODER_PIN_B);

long oldPosition  = -999;
long newPosition;

void setup() {
  Serial.begin(115200); // Inizializzazione della comunicazione seriale
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
}

