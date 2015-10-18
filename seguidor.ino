//Pinos de controle de velocidade do motor no shield recebe valores de 0 a 255
int velocidadeMotor1 = 5;
int velocidadeMotor2 = 6;
//Pinos de controle de sentido da rotação do motor recebe LOW ou HIGH
int motor1 = 7;
int motor2 = 8;
//Pinos analógicos onde os sensores estão conectados
int sensorDireita = A3;
int sensorEsquerda = A4;
//Variáveis que recebem os valores vindos dos sensores
int valorSensorDireita = 0;
int valorSensorEsquerda = 0;
//Valor médio definido para diferenciar a cor da linha
int valorMedio = 650;

void setup() {
  //Define que os pinos serão de saída de dados
  pinMode(velocidadeMotor1, OUTPUT);
  pinMode(velocidadeMotor2, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);    
}

void loop() {
  //Lê os valores dos sensores e mantém os motores desligados no início
  valorSensorDireita = analogRead(sensorDireita);
  valorSensorEsquerda = analogRead(sensorEsquerda);
  analogWrite (velocidadeMotor1, 0);      
  analogWrite (velocidadeMotor2, 0);  

  /*Quando ambos os sensores estiverem na linha 
   * as rodas giram em sentidos opostos para direcionar o carro para frente
   */
  if((valorSensorDireita>valorMedio)&&(valorSensorEsquerda>valorMedio)){
    analogWrite (velocidadeMotor1, 255);      
    analogWrite (velocidadeMotor2, 255); 
    digitalWrite(motor1,LOW);
    digitalWrite(motor2,HIGH);
  }
  /*Quando um dos sensores estiver fora linha 
   * as rodas giram em sentidos iguais para realizar uma curva
   */
  if((valorSensorDireita>valorMedio)&&(valorSensorEsquerda<valorMedio)){
    analogWrite (velocidadeMotor1, 255);      
    analogWrite (velocidadeMotor2, 255); 
    digitalWrite(motor1,LOW);
    digitalWrite(motor2,LOW);
  }
  /*Quando um dos sensores estiver fora linha 
   * as rodas giram em sentidos iguais para realizar uma curva
   */
  if((valorSensorDireita<valorMedio)&&(valorSensorEsquerda>valorMedio)){
    analogWrite (velocidadeMotor1, 255);      
    analogWrite (velocidadeMotor2, 255); 
    digitalWrite(motor1,HIGH);
    digitalWrite(motor2,HIGH);
  }
}
