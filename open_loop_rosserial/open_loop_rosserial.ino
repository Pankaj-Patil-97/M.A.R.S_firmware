/*
  *
  * Project Name: Medical Assistive Robotic System
  * Author List:  Pankaj Patil
  * Filename:     open_loop_rosserial.ino
  * Functions:    move_stepper, get_angle5, get_angle4,get_angle3, get_angle2, get_angle1 
  * Global Variables:   
  * 
  *
*/

/*pinout TIVA-c TM4C123GXL
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

#include <ros.h>
//Header file for recieving joint angles of type std_msgs/Float64
#include <std_msgs/Float64.h>

/*
  *
  * Function Name:  move_stepper
  * Input:    Motor driver terminals-dir_pos, dir_neg, pul_pos, pul_neg, enb_pos, enb_neg, Desired Angle- angle, No of Pulses- pulse
  * Output:   Void  
  * Logic:    Function to move stepper at desired angle, inputs are pin numbers,desired angles
  * Example Call: move_stepper(3,4,5,6,7,8,2.4,4000);
  *
  */

void move_stepper(int dir_pos, int dir_neg, int pul_pos, int pul_neg, int enb_pos, int enb_neg, int angle)
{ 
  int pulse_counter;
  pulse_counter = angle/1.8;
  
  //Enable negative terminal-
  digitalWrite(enb_neg, HIGH);
  //Pulse negative terminal- 
  digitalWrite(pul_neg,LOW);
  
  if(angle<0)
  { //Direction negative terminal LOW for clockwise-
    digitalWrite(dir_neg,LOW);
    digitalWrite(enb_pos, LOW);
    digitalWrite(dir_pos, HIGH);

    for (int x = 0; x < pulse_counter ; x++)
    {
      digitalWrite(pul_pos, HIGH);
      delayMicroseconds(90);
      digitalWrite(pul_pos, LOW);
      delayMicroseconds(90);
    }

    digitalWrite(enb_pos, HIGH);
    delay(100);
  }
  else if(angle>0)
  {
    //Direction negative terminal HIGH for clockwise-
    digitalWrite(dir_neg,HIGH);
    digitalWrite(enb_pos, LOW);
    digitalWrite(dir_pos, LOW);

    for (int x = 0; x < pulse_counter ; x++)
    {
      digitalWrite(pul_pos, HIGH);
      delayMicroseconds(90);
      digitalWrite(pul_pos, LOW);
      delayMicroseconds(90);
    }

    digitalWrite(enb_pos,HIGH);
    delay(100);
  }
}

/*
  *
  * Function Name: get_angle5;
  * Input:    const std_msgs::Float64 &tivac_msg
  * Output:   void
  * Logic:    callbakck function for subscribing to joint 5 angle.  
  * Example Call: 
  *
  */

void get_angle5(const std_msgs::Float64& topic_msg)
{
  //move_stepper();
}

/*
  *
  * Function Name: get_angle4;
  * Input:    const std_msgs::Float64 &tivac_msg
  * Output:   void
  * Logic:    callbakck function for subscribing to joint 5 angle.  
  * Example Call: 
  *
  */

void get_angle4(const std_msgs::Float64& topic_msg)
{ //std_msgs::Float64 xan;
  int angle4 = topic_msg.data;
  //xan = topic_msg.data;
  move_stepper(26,6,25,5,24,4,angle4);
}

/*
  *
  * Function Name: get_angle3;
  * Input:    const std_msgs::Float64 &tivac_msg
  * Output:   void
  * Logic:    callbakck function for subscribing to joint 5 angle.  
  * Example Call: 
  *
  */

void get_angle3(const std_msgs::Float64 &topic_msg)
{
  //move_stepper();
}

/*
  *
  * Function Name: get_angle2;
  * Input:    const std_msgs::Float64 &tivac_msg
  * Output:   void
  * Logic:    callbakck function for subscribing to joint 5 angle.  
  * Example Call: 
  *
  */

void get_angle2(const std_msgs::Float64 &topic_msg)
{
  //move_stepper();
}

/*
  *
  * Function Name: get_angle1;
  * Input:    const std_msgs::Float64 &tivac_msg
  * Output:   void
  * Logic:    callbakck function for subscribing to joint 5 angle.  
  * Example Call: 
  *
  */

void get_angle1(const std_msgs::Float64 &topic_msg)
{
  //move_stepper();
}



//Nodehandler object
ros::NodeHandle ntivac;

//Instantiate subscriber for joint 5 by mentioning topic which this node will suscribe to
ros::Subscriber<std_msgs::Float64> sub5("/gazebo_MARS_prototype/link_4_to_gripper_base_position_controller/command",&get_angle5);

//Instantiate subscriber by mentioning topic which this node will suscribe to
ros::Subscriber<std_msgs::Float64> sub4("/gazebo_MARS_prototype/link_3_to_link_4_position_controller/command", &get_angle4);

//Instantiate subscriber by mentioning topic which this node will suscribe to
ros::Subscriber<std_msgs::Float64> sub3("/gazebo_MARS_prototype/link_2_to_link_3_position_controller/command", &get_angle3);

//Instantiate subscriber by mentioning topic which this node will suscribe to
ros::Subscriber<std_msgs::Float64> sub2("/gazebo_MARS_prototype/base_cylinder_to_link_2_joint_position_controller/command", &get_angle2);

//Instantiate subscriber by mentioning topic which this node will suscribe to
ros::Subscriber<std_msgs::Float64> sub1("/gazebo_MARS_prototype/base_link_to_base_cylinder_position_controller/command", &get_angle1);

void setup() 
{ 
  //setting the baud rate for uart serial communication
  ntivac.getHardware()->setBaud(256000);

  //Inititalises node
  ntivac.initNode();

  //Subscribe to topics
  ntivac.subscribe(sub5);
  ntivac.subscribe(sub4);
  ntivac.subscribe(sub3);
  ntivac.subscribe(sub2);
  ntivac.subscribe(sub1);

  //Output pins for motor driver-
  //Stepper Driver 1-
  pinMode(39,OUTPUT); //pin PF3 DIR-
  pinMode(19,OUTPUT); //pin PB2 DIR+
  pinMode(37,OUTPUT); //pin PC4 EN-
  pinMode(17,OUTPUT); //pin PF0 EN+
  pinMode(18,OUTPUT); //pin PE0 PUL+
  pinMode(38,OUTPUT); //pin PB3 PUL-

  //Stepper Driver 2-
  pinMode(35,OUTPUT); //pin PC6 DIR-
  pinMode(15,OUTPUT); //pin PB7 DIR+
  pinMode(33,OUTPUT); //pin PD6 EN-
  pinMode(13,OUTPUT); //pin PA4 EN+
  pinMode(14,OUTPUT); //pin PB6 PUL+
  pinMode(34,OUTPUT); //pin PC7 PUL-

  //Stepper Driver 3-
  pinMode(35,OUTPUT); //pin PD7 DIR-
  pinMode(15,OUTPUT); //pin PA4 DIR+
  pinMode(33,OUTPUT); //pin PD6 EN-
  pinMode(13,OUTPUT); //pin PA4 EN+
  pinMode(14,OUTPUT); //pin PB6 PUL+
  pinMode(34,OUTPUT); //pin PC7 PUL-

  //Stepper Driver 4-
  pinMode(6,OUTPUT);  //pin PE5 DIR-
  pinMode(5,OUTPUT);  //pin PE4 PUL-
  pinMode(4,OUTPUT);  //pin PB1 EN-
  pinMode(24,OUTPUT); //pin PD1 EN+
  pinMode(25,OUTPUT); //pin PD2 PUL+
  pinMode(26,OUTPUT); //pin PD3 DIR4
  
  //Stepper Driver 5-
  pinMode(35,OUTPUT); //pin PD7 DIR-
  pinMode(15,OUTPUT); //pin PA4 DIR+
  pinMode(33,OUTPUT); //pin PD6 EN-
  pinMode(13,OUTPUT); //pin PA4 EN+
  pinMode(14,OUTPUT); //pin PB6 PUL+
  pinMode(34,OUTPUT); //pin PC7 PUL-

}

void loop() 
{
   ntivac.spinOnce();
  
}
