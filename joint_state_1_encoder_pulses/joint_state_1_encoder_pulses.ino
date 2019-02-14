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
 * 19=PB_2  SCL(0)                39=PF_3
 * 20=GND                         40=PF_2
 * 
 * 
 */

#include <ros.h>
//Include file for sensor_msgs
#include<sensor_msgs/JointState.h>

/*##################################################################*/
/* Encoder */
static double pulse_counter=0;
// ISR - Rising edge

void joint_angle()
{
  switch (digitalRead(23))
  {
   
  case HIGH:  //Serial.print("clockwise");
              pulse_counter++;
              break;
            
  case LOW:   pulse_counter--;
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
ros::Publisher joint_state_pub("/joint_states", &angle_publisher);

//Specifying joint names: Similar to URDF joint declarations.
char *joint_names[]={"base_link_to_wheel1", "base_link_to_wheel2", "base_link_to_wheel3", "base_link_to_wheel4", "manipulator_to_base_link", "base_cylinder_to_link2", "link_2_to_link_3", "link_3_to_link_4", "link_4_to_gripper_base", "gripper_base_to_finger_base1", "finger_base1_to_finger_top1", "gripper_base_to_finger_base2", "finger_base2_to_finger_top2", "gripper_base_to_finger_base3", "finger_base3_to_finger_top3"};

//position variable data type same as sensor_msgs::JointState msg:
//Will only use position inorder to give joint angles.
double pos[15];

//Velocity variable- Not used
double vel[15];

//Effort variable- not used:
double eff[15];

void setup() 
{
  //Setting BAUD rate of tiva-c.
  ntivac.getHardware()-> setBaud(115200);
  
  //Initialising node
  ntivac.initNode();
  ntivac.advertise(joint_state_pub);

  //Channel B input pulse-
  pinMode(23,INPUT);
  //Attaching interrupt from encoder channel A
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3),joint_angle,RISING);

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
  //Timestamping header
  angle_publisher.header.stamp = ntivac.now();

  //Assign joint values:
  angle_publisher.position[5]=pulse_counter;

  //Publish values:
  joint_state_pub.publish(&angle_publisher);
  
  ntivac.spinOnce();
  
}
