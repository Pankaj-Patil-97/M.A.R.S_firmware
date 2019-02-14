/*pinout TIVAc
 * 1=3.3v                       //21=VBUS      
 * 2=PB_5                         22=GND
 * 3=PB_0                         23=PD_0 SCL(3)
 * 4=PB_1                         24=PD_1 SDA(3)
 * 5=PE_4   SCL(2)                25=PD_2
 * 6=PE_5   SDA(2)                26=PD_3
 * 7=PB_4                         27=PE_1
 * 8=PA_5                         28=PE_2
 * 9=PA_6   SCL(1)                29=PE_3        
 * 10=PA_7  SDA(1)                30=PF_1
 * 11=PA_2                        31=PF_4
 * 12=PA_3                        32=PD_7
 * 13=PA_4                        33=PD_6
 * 14=PB_6                        34=PC_7
 * 15=PB_7                        35=PC_6
 * 16=RESET                       36=PC5
 * 17=PF_0                        37=PC_4
 * 18=PE_0                        38=PB_3 SDA(0)
 * 19=PB_2 SCL(0)                 39=PF_3
 * 20=GND                         40=PF_2
 * 
 * 
 */
volatile int joint_angle=0;
bool z_index=0;
volatile int direction;

void pulse_counts()
{
  //Serial.println(digitalRead(23));
  //Pin no:2 is PB_5
  //delayMicroseconds(10);
  switch (digitalRead(23))
  {
   
  case HIGH:  //Serial.println("CLOCKWISE");
              //PB0=pin no 3
              joint_angle++;
              //digitalWrite(RED_LED,HIGH);
              break;
              //joint_angle=joint_angle*0.36;
            
  case LOW:   //Serial.println("ANTICLOCKWISE");
              joint_angle--;
              //digitalWrite(RED_LED,LOW);
              break;
  
  default:    break;
              //joint_angle=joint_angle*0.36;
  }
}

void setup() 
{ 
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(23,INPUT);
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), pulse_counts, FALLING);  
}

void loop() 
{  //noInterrupts();
   //joint_angle=joint_angle*0.36;
   //direction=digitalRead(3);
   Serial.println("Loop reading");
   Serial.println(joint_angle);
   //delay(5000);
   for(int i=0; i++; i<=9000);

}
