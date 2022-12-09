#include <Arduino.h>

#define Sensor_Som 7 // Pino sensor de som
#define red 3
#define green 5 
#define blue 6
#define tempo_maximo_de_uma_palma 150
#define tempo_maximo_entre_palmas 500

int contPalmas = 0; // Contador de Palmas
unsigned long tempo_espera = 0;
unsigned long tempo_espera_entre_palmas = 0;

void setup() {
  pinMode(Sensor_Som, INPUT); // Inicia o pino do sensor como entrada
  pinMode(red, OUTPUT); // Inicia os pino do rele como saída
}

void palmas(){
  int sensor_palmas = digitalRead(Sensor_Som);

  if(sensor_palmas == 0){ //Se detectar uma palma

    if(tempo_espera == 0){
      tempo_espera = tempo_espera_entre_palmas = millis();
      contPalmas++;
    }
    else if(millis()-tempo_espera > tempo_maximo_de_uma_palma){
      tempo_espera = 0;
    }
  }
  
  else if((contPalmas !=0) && (millis()-tempo_espera_entre_palmas > tempo_maximo_entre_palmas)){
      contPalmas = 0;
      on_off();
      // tempo_espera_entre_palmas = 0;
  }
}

void on_off(){
  switch (contPalmas)
  {
  case 1:
    digitalWrite(red,!digitalRead(red));
    break;
  
  case 2:
    
    break;
  }
}

void loop() {
  palmas();
  on_off();
}