/*
  *
  * Project Name: Medical Assistive Robotic System
  * Author List:  Pankaj Patil
  * Filename:     mars_joint_state_publisher.cpp
  * Functions:    <Comma separated list of Functions defined in this file>
  * Global Variables: <List of all the global variables defined in this file, None if no global 
  *     variables>
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
//Include file for sensor_msgs
#include<sensor_msgs/JointState.h>

// Joint angle variables
double joint_1;
double joint_2;
double joint_3;
double joint_4;
double joint_5;
/*##################################################################*/
/* Encoder Data calculation for joint 1 */
double pulse_counter1=0;
//ISR - Rising edge

void joint_1_angle()
{
  switch (digitalRead(23))
  {
   
  case HIGH:  //Serial.print("clockwise");
              pulse_counter1++;
              break;
            
  case LOW:   pulse_counter1--;
              break;
  
  default:    break;
  }
}


/*##################################################################*/

/*##################################################################*/
/* Encoder Data calculation for joint 2 */
double pulse_counter2=0;
//ISR - Rising edge

void joint_2_angle()
{
  switch (digitalRead(24))
  {
   
  case HIGH:  //Serial.print("clockwise");
              pulse_counter2++;
              break;
            
  case LOW:   pulse_counter2--;
              break;
  
  default:    break;
  }
}


/*##################################################################*/

/*##################################################################*/
/* Encoder Data calculation for joint 3 */
double pulse_counter3=0;
//ISR - Rising edge

void joint_3_angle()
{
  switch (digitalRead(25))
  {
   
  case HIGH:  //Serial.print("clockwise");
              pulse_counter3++;
              break;
            
  case LOW:   pulse_counter3--;
              break;
  
  default:    break;
  }
}


/*##################################################################*/

/*##################################################################*/
/* Encoder Data calculation for joint 3 */
double pulse_counter4=0;
//ISR - Rising edge

void joint_4_angle()
{
  switch (digitalRead(26))
  {
   
  case HIGH:  //Serial.print("clockwise");
              pulse_counter4++;
              break;
            
  case LOW:   pulse_counter4--;
              break;
  
  default:    break;
  }
}


/*##################################################################*/

/*##################################################################*/
/* Encoder Data calculation for joint 3 */
double pulse_counter5=0;
//ISR - Rising edge

void joint_5_angle()
{
  switch (digitalRead(27))
  {
   
  case HIGH:  //Serial.print("clockwise");
              pulse_counter5++;
              break;
            
  case LOW:   pulse_counter5--;
              break;
  
  default:    break;
  }
}


/*##################################################################*/

//Nodehandler object
ros::NodeHandle ntivac;

//Instantiating Angle publisher message:
sensor_msgs::JointState angle_publisher;

//Instantiating publisher object:
ros::Publisher joint_state_pub("/hardware_states", &angle_publisher);

//Specifying joint names: Similar to URDF joint declarations.
char *joint_names[]={"base_link_to_wheel1", "base_link_to_wheel2", "base_link_to_wheel3", "base_link_to_wheel4", "manipulator_to_base_link", "base_cylinder_to_link2", "link_2_to_link_3", "link_3_to_link_4", "link_4_to_gripper_base", "gripper_base_to_finger_base1", "finger_base1_to_finger_top1", "gripper_base_to_finger_base2", "finger_base2_to_finger_top2", "gripper_base_to_finger_base3", "finger_base3_to_finger_top3"};

//position variable of data type as same as sensor_msgs::JointState msg:
//Will only use position inorder to give joint angles.
double pos[15];

//Velocity variable- Not used
double vel[15];

//Effort variable- not used:
double eff[15];

void setup() 
{
  //Setting BAUD rate of tiva-c.
  ntivac.getHardware()-> setBaud(256000);
  
  //Initialising node
  ntivac.initNode();
  ntivac.advertise(joint_state_pub);

  //Encoder 1 Channel B input pulse-
  pinMode(23,INPUT);
  //Attaching interrupt from encoder 1 channel A
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3),joint_1_angle,RISING);

  //Encoder 2 Channel B input pulse
  pinMode(24,INPUT);
  //Attaching interrupt from encoder 2 channel A
  pinMode(4,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(4),joint_2_angle,RISING);

  //Encoder 3 Channel B input pulse
  pinMode(25,INPUT);
  //Attaching interrupt from encoder 3 channel A
  pinMode(5,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(5),joint_3_angle,RISING);

  //Encoder 4 Channel B input pulse
  pinMode(26,INPUT);
  //Attaching interrupt from encoder 4 channel A
  pinMode(6,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(6),joint_4_angle,RISING);

  //Encoder 5 Channel B input pulse
  pinMode(27,INPUT);
  //Attaching interrupt from encoder 5 channel A
  pinMode(7,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7),joint_5_angle,RISING);
  
  //Defining length of each array in sensor_msgs::JointState message:
  angle_publisher.name_length = 15;
  angle_publisher.position_length=15;
  angle_publisher.velocity_length=0;
  angle_publisher.effort_length=0;

  angle_publisher.name = joint_names;
  angle_publisher.position = pos;
  angle_publisher.velocity = vel;
  angle_publisher.effort = eff;
  
}

void loop() 
{ 
  //Encoder angle from pulses-
  joint_1 = pulse_counter1*0.006282;
  joint_2 = pulse_counter2*0.006282;
  joint_3 = pulse_counter3*0.006282;
  joint_4 = pulse_counter4*0.006282;
  joint_5 = pulse_counter5*0.006282;
  
  
  //Timestamping header
  angle_publisher.header.stamp = ntivac.now();

  //Assign joint values:
  angle_publisher.position[4]=joint_2;
  angle_publisher.position[5]=joint_1;
  angle_publisher.position[6]=joint_3;
  angle_publisher.position[7]=joint_4;
  angle_publisher.position[8]=joint_5;



  //Publish values:
  joint_state_pub.publish(&angle_publisher);
  
  ntivac.spinOnce();
  
}
