#include "Stepper.h"

#define STEPS 32


int direccion;
Stepper stepper(STEPS, 8, 10, 9, 11);
//variables para pulsadores
int pulsadorNivel1 = 16;
int pulsadorNivel2 = 17;
int pulsadorNivel3 = 12;
int pulsadorNivel4 = 14;
int pulsadorNivel5 = 15;
//variables para sensores
int sensorNivel1 = 5;
int sensorNivel2 = 4;
int sensorNivel3 = 3;
int sensorNivel4 = 2;
int sensorNivel5 = 6;
int val;   //variable que almacena su valor en memoria y que sirve para detectar un nivel

void setup() {
  pinMode(sensorNivel1, INPUT);
  pinMode(sensorNivel2, INPUT);
  pinMode(sensorNivel3, INPUT);
  pinMode(sensorNivel4, INPUT);
  pinMode(pulsadorNivel1, INPUT);
  pinMode(pulsadorNivel2, INPUT);
  pinMode(pulsadorNivel3, INPUT);
  pinMode(pulsadorNivel4, INPUT);
  Serial.begin(9600);
}

void loop() {
  //-------------------------------------------------------------Nivel 1---------------------------------------------------------------------------
  if (digitalRead(pulsadorNivel1) == HIGH) { //baja al nivel 1
    val = 1;
    while (digitalRead(sensorNivel1) == HIGH) {
      stepper.setSpeed(500);
      direccion = 200;    //el motor se mueve en sentido horario
      stepper.step(direccion);  //se establece direccion del motor
      Serial.println("Estoy bajando al nivel 1");
    }
  }

  //---------------------------------------------------------------------Nivel 2------------------------------------------------------------------------
  if (digitalRead(pulsadorNivel2) == HIGH && (digitalRead(sensorNivel1) == LOW)) {  //sube del nivel 1 al 2
    val = 2;
    while (digitalRead(sensorNivel2) == HIGH) {
      stepper.setSpeed(500);
      direccion  =  -200;  // rota en sentido contrario al reloj
      stepper.step(direccion);
      Serial.println("subo al nivel 2 ");
    }
  } else if (digitalRead(pulsadorNivel2) == HIGH && (digitalRead(sensorNivel3) == LOW ||
    digitalRead(sensorNivel4) == LOW || digitalRead(sensorNivel5)==LOW) )  { //baja al nivel 2 desde el nivel 3, 4 o 5
    val = 2;
    while (digitalRead(sensorNivel2) == HIGH) {
      stepper.setSpeed(500);
      direccion  =  200;  // rota en sentido del reloj
      stepper.step(direccion);
      Serial.println("bajo al nivel 2");
    }
  }
  //----------------------------------------------------Nivel 3 -------------------------------------------------------------------
  if (digitalRead(pulsadorNivel3) == HIGH && ((digitalRead(sensorNivel1) == LOW) || (digitalRead(sensorNivel2) == LOW) ) ) { //sube al nivel 3 desde el nivel 1 o 2
    val = 3;
    while (digitalRead(sensorNivel3) == HIGH) {
      stepper.setSpeed(500);
      direccion  =  -200;  // rota en sentido contrario al reloj
      stepper.step(direccion);
      Serial.println("subo al nivel 3");
    }
  } else if (digitalRead(pulsadorNivel3) == HIGH && (digitalRead(sensorNivel4) == LOW || digitalRead(sensorNivel5)==LOW)) { //baja al nivel 3 desde el nivel 4 o 5
    val = 3;
    while (digitalRead(sensorNivel3) == HIGH) {
      stepper.setSpeed(500);
      direccion  =  200;  // rota en sentido del reloj
      stepper.step(direccion);
      Serial.println("bajo al nivel 3 ");
    }
  }

  //----------------------------------------------------Nivel 4---------------------------------------------------------------------
  if (digitalRead(pulsadorNivel4) == HIGH && (digitalRead(sensorNivel1)==LOW ||digitalRead(sensorNivel2)==LOW || digitalRead(sensorNivel3)==LOW)) { //sube al nivel 4 desde 1, 2, 3
    val = 4;
    while (digitalRead(sensorNivel4) == HIGH) {
      stepper.setSpeed(500);
      direccion  =  -200;  // rota en sentido contrario reloj
      stepper.step(direccion);
      Serial.println("subo al nivel 4");3
    }
  }else if(digitalRead(pulsadorNivel4)==HIGH && digitalRead(sensorNivel5)==LOW){ // baja al nivel 4 desde el 5
        val = 4;
    while (digitalRead(sensorNivel4) == HIGH) {
      stepper.setSpeed(500);
      direccion  =  200;  // rota en sentido del reloj
      stepper.step(direccion);
      Serial.println("bajo al nivel 4 ");
    }
  }
    //----------------------------------------------------Nivel 5---------------------------------------------------------------------
  if (digitalRead(pulsadorNivel5) == HIGH ) { //sube al nivel 5
    val = 5;
    while (digitalRead(sensorNivel5) == HIGH) {
      stepper.setSpeed(500);
      direccion  =  -200;  // rota en sentido contrario reloj
      stepper.step(direccion);
      Serial.println("subo al nivel 5");
    }
  }
  //------------------------------------------------------------------parar ascensor----------------------------------------------------------------
  if (((digitalRead(sensorNivel1) == LOW) && val == 1) || ((digitalRead(sensorNivel2) == LOW) && val == 2) || ((digitalRead(sensorNivel3) == LOW) && val == 3) ||
      ((digitalRead(sensorNivel4) == LOW) && val == 4) || ((digitalRead(sensorNivel5)==LOW) && val == 5))  {
    stepper.setSpeed(500);
    direccion = 0;      //se detiene el motor
    stepper.step(direccion);  //se establece direccion del motor
    Serial.println("paré el motor");
  }
  //------------------------------------------------------------------------------------------------------------------------------------
  Serial.println(val);
  Serial.println(direccion);


}
