#include "ESP_MICRO.h"


#define trigPin 13
#define t2 0
#define slot3 14
#define slot4 12


long duration;
int distance;

int S1 = 0, S2 = 0, S3=0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot = 4, total = 0;
int d1, d2, dis1, dis2;

int x, pos = 0;

void Read_Sensor(){
  S1 = 0, S2 = 0, S3=0, S4=0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  d1 = pulseIn(slot3, HIGH);
  
  digitalWrite(t2, LOW);
  delayMicroseconds(2);
  digitalWrite(t2, HIGH);
  delayMicroseconds(10);
  digitalWrite(t2, LOW);
  d2 = pulseIn(slot4, HIGH);
  dis1 = d1*0.034/2;
  dis2 = d2*0.034/2;
  
  Serial.print(dis1+"\t");
  if(dis1 <=20){S3 = 1;}
  if(dis2 <=20){S4 = 1;}
  
}

void setup(){
  
  Serial.begin(115200);
  Serial1.begin(115200);
  start("ANUJ-PC 8708","abcd12345");
  
  
  pinMode(trigPin, OUTPUT);
  pinMode(t2, OUTPUT);
  pinMode(slot3, INPUT);
  pinMode(slot4, INPUT);

  
  delay(2000);
  Read_Sensor();
  total = S1+S2;
  slot = slot-total;
}

bool flg = true;
void loop(){
  waitUntilNewReq();
  String s = "";//Waits until a new request from python come
  if(1){
    Read_Sensor();
    delay(1000);
  
    if(S3 == 1){s = s+"S3: Fill,";}
    else{s = s+"S3: Empty,";}
    
    if(S4 == 1){s = s+"S4: Fill,";}
    else{s = s+"S4: Empty,";}
    
    if(S3 == 0 || S4 == 0){
      if(flg){
        Serial1.println("1");
        //Serial1.println("0");
        delay(5000);
        flg =!flg;
      }else{
        flg=!flg;
      }
      
      s = s+"Ok";
    }else{
      s = s+"No Slots Available";
    }
    returnThisStr(s);
    x=0;
  }
  
}
