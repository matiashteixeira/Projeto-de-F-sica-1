#include <Arduino.h>

#define Sensor_Som A0 // Pino sensor de som
#define tempo_maximo_de_uma_palma 150
#define tempo_maximo_entre_palmas 500
#define vermelho 11
#define verde 10
#define azul 9
#define btn 2

int contPalmas = 0; // Contador de Palmas
int contagem = 0;
unsigned long tempo_espera = 0;
unsigned long tempo_espera_entre_palmas = 0;
bool temporiza = 1, btn_clicado = 0;
int alterna_modo = 0;
int sensor_palmas;

void setup() {
  pinMode(Sensor_Som, INPUT); // Inicia o pino do sensor como entrada
  pinMode(vermelho, OUTPUT); // Inicia os pino como saída
  pinMode(verde, OUTPUT); // Inicia os pino como saída
  pinMode(azul, OUTPUT); // Inicia os pino como saída
  pinMode(btn,INPUT); // Inicia o pino com entrada
  Serial.begin(9600);
}

void palmas(){
  if(503 - analogRead(Sensor_Som) > 10 or 503 - analogRead(Sensor_Som) < -10)
    sensor_palmas = 0;
  else
    sensor_palmas = 1;

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
  }
}

void on_off(){
  switch (contPalmas)
  {
  case 1:
    digitalWrite(vermelho,LOW);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
    break;
  
  case 2:
    digitalWrite(vermelho,HIGH);
    digitalWrite(azul,HIGH);
    digitalWrite(verde,HIGH);
    break;

  }
}

void musica_opcao1(){

  if(503 - analogRead(Sensor_Som) > 10 or 503 - analogRead(Sensor_Som) < -10){
    
    if(temporiza){
      contagem++;
      if(contagem == 900)
        temporiza = 0;
    }else{
      contagem--;
      if(contagem == 0)
        temporiza = 1;
    }
    if(contagem >= 0 && contagem <= 100){
      analogWrite(vermelho,255);
      analogWrite(verde,0);
      analogWrite(azul,0);
    }
    else if(contagem > 100 && contagem <= 200){
      analogWrite(vermelho,170);
      analogWrite(verde,85);
      analogWrite(azul,0);
    }
    else if(contagem > 200 && contagem <= 300){
      analogWrite(vermelho,85);
      analogWrite(verde,170);
      analogWrite(azul,0);
    }
    else if(contagem > 300 && contagem <= 400){
      analogWrite(vermelho,0);
      analogWrite(verde,255);
      analogWrite(azul,0);
    }
    else if(contagem > 400 && contagem <= 500){
      analogWrite(vermelho,0);
      analogWrite(verde,170);
      analogWrite(azul,85);
    }
    else if(contagem > 500 && contagem <= 600){
      analogWrite(vermelho,0);
      analogWrite(verde,85);
      analogWrite(azul,170);
    }
    else if(contagem > 600 && contagem <= 700){
      analogWrite(vermelho,0);
      analogWrite(verde,0);
      analogWrite(azul,255);
    }
    else if(contagem > 700 && contagem <= 800){
      analogWrite(vermelho,85);
      analogWrite(verde,0);
      analogWrite(azul,170);
    }
    else if(contagem > 800 && contagem <= 900){
      analogWrite(vermelho,170);
      analogWrite(verde,0);
      analogWrite(azul,85);
    }
  }
  else{
    analogWrite(vermelho,0);
    analogWrite(verde,0);
    analogWrite(azul,0);
  }
}

void musica_branco(){
  if(503 - analogRead(Sensor_Som) > 10 or 503 - analogRead(Sensor_Som) < -10){
    digitalWrite(vermelho,HIGH);
    digitalWrite(azul,HIGH);
    digitalWrite(verde,HIGH);
  }else{
    digitalWrite(vermelho,LOW);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
  }
}

void musica_azul(){
  if(503 - analogRead(Sensor_Som) > 10 or 503 - analogRead(Sensor_Som) < -10){
    digitalWrite(vermelho,LOW);
    digitalWrite(azul,HIGH);
    digitalWrite(verde,LOW);
  }else{
    digitalWrite(vermelho,LOW);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
  }
}

void musica_vermelha(){
  if(503 - analogRead(Sensor_Som) > 10 or 503 - analogRead(Sensor_Som) < -10){
    digitalWrite(vermelho,HIGH);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
  }else{
    digitalWrite(vermelho,LOW);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
  }
}

void musica_verde(){
  if(503 - analogRead(Sensor_Som) > 10 or 503 - analogRead(Sensor_Som) < -10){
    digitalWrite(vermelho,LOW);
    digitalWrite(azul,LOW);
    digitalWrite(verde,HIGH);
  }else{
    digitalWrite(vermelho,LOW);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
  }
}

void botao(){
  if(digitalRead(btn)){
    btn_clicado = 1;
  }
  
  if(!digitalRead(btn) and btn_clicado){
    btn_clicado = 0;
    Serial.println(alterna_modo);
    
    if(alterna_modo >= 5){
      alterna_modo = 0;
    }else{
    alterna_modo++;
    }
    
  }
}

void loop() {
  botao();
  Serial.println(digitalRead(btn));
  switch (alterna_modo)
  {
  case 0:
    palmas();
    on_off();
    break;

  case 1:
    //Serial.println("azul");
    musica_azul();
    break;

  case 2:
    musica_verde();
    break;

  case 3:
    musica_vermelha();
    break;

  case 4:
    musica_branco();
    break;
  
  case 5:
    //Serial.println("colorido");
    musica_opcao1();
    break;
  }
}