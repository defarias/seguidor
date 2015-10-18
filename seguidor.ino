#include <Ultrasonic.h>
#include <Wire.h>
#define echoPino 13
#define triggerPino 12
Ultrasonic ultrasonic(12,13);

int velocidadeMotor1 = 5;
int velocidadeMotor2 = 6;
int motor1 = 7;
int motor2 = 8;
int sensorDireita = A3;
int sensorEsquerda = A4;
int valorSensorDireita = 0;
int valorSensorEsquerda = 0;
int valorMedio = 650;
float distancia;
long tempo;

void setup() {
  pinMode(velocidadeMotor1, OUTPUT);
  pinMode(velocidadeMotor2, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);    
}

void loop() {
 /* tempo = ultrasonic.timing();
  distancia = ultrasonic.convert(tempo, Ultrasonic::CM); 

  if(distancia<3){
    analogWrite (velocidadeMotor1, 0);      
    analogWrite (velocidadeMotor2, 0);
    delay(10000);
  }else{*/  
    valorSensorDireita = analogRead(sensorDireita);
    valorSensorEsquerda = analogRead(sensorEsquerda);    
      
    if((valorSensorDireita>valorMedio)&&(valorSensorEsquerda>valorMedio)){
      analogWrite (velocidadeMotor1, 200);      
      analogWrite (velocidadeMotor2, 200); 
      digitalWrite(motor1,LOW);
      digitalWrite(motor2,HIGH);
    }
    if((valorSensorDireita>valorMedio)&&(valorSensorEsquerda<valorMedio)){
      analogWrite (velocidadeMotor1, 200);      
      analogWrite (velocidadeMotor2, 200); 
      digitalWrite(motor1,LOW);
      digitalWrite(motor2,LOW);
    }
    if((valorSensorDireita<valorMedio)&&(valorSensorEsquerda>valorMedio)){
      analogWrite (velocidadeMotor1, 200);      
      analogWrite (velocidadeMotor2, 200); 
      digitalWrite(motor1,HIGH);
      digitalWrite(motor2,HIGH);
    }
  /*}*/
}
