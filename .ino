#include <Servo.h>
Servo myservo;
Servo mybldc;
int pos1=0;
int poss1=0;
int pos2=0;
int poss2=0;
int a=0;
int b=0;
int servopin=9;
int bldcpin=10;
unsigned long timer1=0;
unsigned long timer2=0;

void setup(){
Serial.begin(9600);
  myservo.attach(servopin);
  mybldc.attach(bldcpin);
}

void loop(){
while(Serial.available()==0);
  String val=Serial.readString();
  if(val=="a"){
    //Serial.println(val); //only for inspection.
    delay(1000);
  Serial.println("Initiating preflight checkup sequence...");
    delay(3000);
  Serial.println("Inspecting Flaps...");
    delay(1000);
    while(timer1<=5){
      Serial.println(timer1);
      timer1+=1;
      if(timer1==3){
        Serial.println("Flaps Checked.");
        break;
      }
      for(pos1=0;pos1<=180;pos1+=1){
        myservo.write(pos1);
        delay(15);
      }  
      for(pos1=180;pos1>=0;pos1-=1){
        myservo.write(pos1);
        delay(15);
      }
    } 
    delay(3000);
    Serial.println("Inspecting propeller...");
    for(pos2=0;pos2<=60;pos2+=1){
      mybldc.write(pos2);
      //Serial.println(pos2);//only for inspection.
        delay(150); //hints:(v/1000)*60= time to read 0-60
    }
    for(pos2=60;pos2<=65;pos2+=1){
      mybldc.write(pos2);
      delay(1000);
      Serial.println(a);
      a+=1;
    }
    for(pos2=65;pos2>=55;pos2-=1){
      mybldc.write(pos2);
      delay(150);
      //Serial.println(pos2);//only for inspection.
      }
    Serial.println("Propeller Checked.");
    delay(2000);
    Serial.println("All System Checked.");
    delay(2000);
    Serial.println("Transferring Controls to Manual Input...");
    delay(3000);
    for(poss2=0;poss2<=57;poss2+=1){
          mybldc.write(poss2);
          //Serial.println(poss2);//only for inspection.
          }
    Serial.println("Prompted to Manual Control.");
    while(val=="a"){
    while(Serial.available()==0);
    int vall=Serial.read();
        if(vall=='w'){
        mybldc.write(poss2);
        //Serial.println(poss2);//only for inspection.
        poss2+=1;
        Serial.println(b);
        b+=1;  
      }
      else if(vall=='s'){
        if(poss2>=58){
      mybldc.write(poss2);
        //Serial.println(poss2);//only for inspection.
        poss2-=1;
        Serial.println(b);
        b-=1;
        }
      }
      else if(vall=='o'){
        if(poss1<=180){
      myservo.write(poss1);
      Serial.println(poss1);
        poss1+=1;
        }
      }
      else if(vall=='l'){
        if(poss1>=0){
      myservo.write(poss1);
      Serial.println(poss1);
        poss1-=1;
        
        }
      }
      else if(vall=='e'){
        Serial.println("\nWarning!, you are Exiting the System loop.");
        Serial.println("\nEnter 'y' to exit OR 'n' to continue:");
        while(Serial.available()==0);
        String vali=Serial.readString();
        if(vali=="y"){
          Serial.println("System Exited.");
          break;
          }
          else if(vali=="n"){
            Serial.println("Continuing the System loop.");
            }
            else{
              Serial.println("Level-3 Warning!: INVALID Input.");
              }
        }
      else{
      Serial.println("Level-2 Warning!: INVALID Input.");
      }
    }  
  }
  else{
    Serial.println("Level-1 Warning!: Command not found.");
  }
}