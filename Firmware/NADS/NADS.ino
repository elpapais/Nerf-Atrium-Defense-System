#include <Servo.h> 
 
Servo fire;  
Servo pan;
Servo tilt;

int tiltPos=180;
int panPos=180;

boolean moveFlag = 0;

int time = 0;
int timer = 0;

char inKey;
 
void setup() 
{ 
  fire.attach(9);  
  
  fire.write(110);
  delay(1000);
  fire.detach();

pinMode(2, INPUT);
digitalWrite(2, HIGH);
pinMode(3, INPUT);
digitalWrite(3, HIGH);
pinMode(4, INPUT);
digitalWrite(4, HIGH);
pinMode(5, INPUT);
digitalWrite(5, HIGH);
pinMode(6, INPUT);
digitalWrite(6, HIGH);
pinMode(A5, INPUT);
digitalWrite(A5, HIGH);
pinMode(7, OUTPUT);
   digitalWrite(7, LOW);

Serial.begin(9600);

  
} 
 
void loop() 
{  
  entice();
  
  while(time>0){
      digitalWrite(7, HIGH);
  timerUpdate();
  
  if(digitalRead(3)==LOW){tiltPos--; moveFlag=1;}
  if(digitalRead(6)==LOW){tiltPos++; moveFlag=1;}
  if(digitalRead(4)==LOW){panPos--; moveFlag=1;}
  if(digitalRead(5)==LOW){panPos++; moveFlag=1;}  
  
  panPos=constrain(panPos,0,179);
  tiltPos=constrain(tiltPos,0,179);
  
    if(!moveFlag){
  tilt.detach();    
  pan.detach();  }
  
  if(moveFlag){
    tilt.attach(10);
    pan.attach(8);
  tilt.write(tiltPos);       
  pan.write(panPos);  
  delay(10);
  moveFlag=0;}
  

  
  
  if(digitalRead(2)==LOW){
    
  tilt.detach();    
  pan.detach();  
//  digitalWrite(7, HIGH);
//  delay(2000);
    fire.attach(9);
    fire.write(180);
    delay(1000);
    fire.write(110);
    delay(500);
 //     digitalWrite(7, LOW);
    fire.detach();
    tilt.attach(10);    
     pan.attach(8); }
   
 // Serial.print("tilt: ");
 // Serial.print(tiltPos);
 // Serial.print("pan: ");
 // Serial.println(panPos);
   
    
} }

void entice(){

while(time<1){
  
  while (Serial.available() > 0) {
      inKey = Serial.read();
      Serial.print(inKey);
      
      if (inKey==0x01){time = 2;};
      if (inKey==0x05){time = 10;};
      if (inKey==0x0A){time = 20;};
      if (inKey==0x19){time = 50;};
       Serial.print("v");
 Serial.print(time); 
      
}
  tilt.detach();pan.detach();digitalWrite(7, LOW); 
}
Serial.print("v");
Serial.print("fire");
delay(500);
Serial.print("v");
delay(500);
Serial.print("fire");
delay(500);
Serial.print("v");
delay(500);
Serial.print("fire");
delay(500);
Serial.print("v");
delay(500);
}

void timerUpdate(){
 
 timer++;
 if(timer>15000){ 
 time--;
 Serial.print("v");
 Serial.print(time); 
 timer=0;}
  
}
