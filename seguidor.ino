//Inclui bibliotecas
#include <Ultrasonic.h>
#include <TimerOne.h>

//Define os pinos de controle do sensor ultrassonico
#define echoPino 13 
#define triggerPino 12
Ultrasonic ultrasonico(12,13);

//Pinos de controle de velocidade do motor no shield recebe valores de 0 a 255
int velocidadeMotor1 = 5;
int velocidadeMotor2 = 6;

//Pinos de controle de sentido da rotação do motor recebe LOW ou HIGH
int motor1 = 7;
int motor2 = 8;

//Pinos analógicos onde os sensores de refletância estão conectados
int sensorDireita = A3;
int sensorEsquerda = A4;

//Variáveis que recebem os valores vindos dos sensores
int valorSensorDireita = 0;
int valorSensorEsquerda = 0;

//Valor médio definido para diferenciar a cor da linha
int valorMedio = 750;

//Armazena valor da distancia de um obstaculo
int distancia = 99;

//Variaveis de controle do metodo de detectar obstaculo
int contador = 0;
int obstaculo = 0;

void setup() {
  //Define se os pinos seráo de saida ou entrada de dados
  pinMode(velocidadeMotor1, OUTPUT);
  pinMode(velocidadeMotor2, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(echoPino, INPUT); 
  pinMode(triggerPino, OUTPUT);
  
  /*Define um tempo especifico para chamar uma função  
   *Define a função a ser chamada no tempo definido
  */
  Timer1.initialize(500000);
  Timer1.attachInterrupt(detectarObstaculo);
}
void loop() {
  /*Checa se existe obstaculo a menos de  5 centimetros*/
  if(distancia<21){
    /*Encontrou obstaculo*/
    obstaculo = 1;
    /*Para os motores por 10 segundos*/
    analogWrite (velocidadeMotor1, 0);      
    analogWrite (velocidadeMotor2, 0);
    delay(10000);
  }else{  
     /*Lê os valores dos sensores de refletância*/
     valorSensorDireita = analogRead(sensorDireita);
     valorSensorEsquerda = analogRead(sensorEsquerda);
     analogWrite (velocidadeMotor1, 0);      
     analogWrite (velocidadeMotor2, 0);
     /*Quando ambos os sensores estiverem na linha 
     * as rodas giram em sentidos opostos para direcionar o carro para frente
     */
     if((valorSensorDireita>valorMedio)&&(valorSensorEsquerda>valorMedio)){
       analogWrite (velocidadeMotor1, 175);      
       analogWrite (velocidadeMotor2, 175); 
       digitalWrite(motor1,LOW);
       digitalWrite(motor2,HIGH);
     }
     /*Quando um dos sensores estiver fora linha 
     * as rodas giram em sentidos iguais para realizar uma curva
     */
     if((valorSensorDireita>valorMedio)&&(valorSensorEsquerda<valorMedio)){
       analogWrite (velocidadeMotor1, 175);      
       analogWrite (velocidadeMotor2, 175); 
       digitalWrite(motor1,LOW);
       digitalWrite(motor2,LOW);
     }
     /*Quando um dos sensores estiver fora linha 
     * as rodas giram em sentidos iguais para realizar uma curva
     */
     if((valorSensorDireita<valorMedio)&&(valorSensorEsquerda>valorMedio)){
        analogWrite (velocidadeMotor1, 175);      
        analogWrite (velocidadeMotor2, 175); 
        digitalWrite(motor1,HIGH);
        digitalWrite(motor2,HIGH);
     }
  }
}
void detectarObstaculo(){
  //Só faz a leitura se não houver detectado obstaculo
  if(obstaculo == 1){
    //Contador para controlar o tempo de leitura
    if(contador<=40){
      obstaculo = 1;
      contador++; 
      //Apos 10 segundos ele libera distancia para movimentar os motores
      if(contador==20){
        distancia = 99;
      }
    }else{
      //Reseta para permitir novas leituras
      contador = 0;
      obstaculo = 0;
    }
  }else{ 
    //Desliga o pino e calcula o tempo de resposta entre pino baixo e alto
    digitalWrite(triggerPino, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPino, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPino, LOW);
    //Calcula a distância do objeto
    distancia = ultrasonico.Ranging(CM); 
  }
}
 
