//variaveis para motor
int pino = 5;

int valuePWM = 90;
double cicloTrabalho = (valuePWM*100)/255;
double Vout = 5*(cicloTrabalho/100);
int speedAtual = valuePWM;

//variaveis para sensor encoder
int pino_encoder = 2;
long int rpm;
volatile byte pulsos;
unsigned long timeold;
unsigned int pulsos_por_volta = 2; //numeros de fresta do disco encoder
int intervalo = 500;

void contador()
{
  pulsos++;
}

void setup() {
  Serial.begin(115200);

  //configurando pinos
  pinMode(pino, OUTPUT);
  pinMode(pino_encoder, INPUT);

  //Interrupcao para 0 = Pino digital 2
  attachInterrupt(0, contador, RISING);

  pulsos = 0;
  rpm = 0;
  timeold = 0;
  
  while(!Serial);
  analogWrite(pino, speedAtual);
  //Serial.println("Velocidade > 0 e < 255");    
}

void loop() { 
  //speedAtual = Serial.parseInt();
  /*if(speedAtual >= 0 && speedAtual <= 255){             
    analogWrite(pino, speedAtual);             
  }*/
   
  if(millis() - timeold >= intervalo) {
    //desabilitando interrupcao durante o calculo
    detachInterrupt(0);
    rpm = (60*intervalo / pulsos_por_volta)/(millis()-timeold)*pulsos;
    timeold = millis();
    pulsos = 0;    
    attachInterrupt(0, contador, RISING);
    
    Serial.println(rpm); 
  }  
  
  //Serial.print(Vout); 
  //Serial.print(" ");  
  //Serial.print(timeold);
  //Serial.print(" "); 
  //Serial.println(rpm);   
  delay(100); 
}
