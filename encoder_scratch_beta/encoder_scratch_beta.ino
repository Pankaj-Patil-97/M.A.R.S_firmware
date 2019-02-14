//#include <ros.h>
//#include <std_msgs/Float64.h>
//#include <Arduino.h>
//#include <Wiring.h>

volatile int joint_angle=0;
bool z_index=0;
volatile int direction;

void angle_calculator()
{
  //Pin no:2 is PB_5
  
  if(digitalRead(3)==HIGH)
  { 
    Serial.println("C");
  }
  else 
  { 
    Serial.println("A");
  }
}

void setup() 
{ 
  Serial.begin(9600);
  pinMode(24,OUTPUT);
  pinMode(2,INPUT);
  pinMode(23,INPUT_PULLUP); //B
  pinMode(3,INPUT_PULLUP);//A
  attachInterrupt(digitalPinToInterrupt(3), angle_calculator, RISING); 
  
}

void loop() 
{  //noInterrupts();
   //joint_angle=joint_angle*0.36;
   direction=digitalRead(3);
   digitalWrite(24,digitalRead(23));
   //Serial.println("Loop reading");
   //Serial.println(joint_angle);
   //delay(1000);
}
