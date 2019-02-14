//Including header files for communication with ROS 
#include<ros.h>
//Header file for std_msgs data type
#include<std_msgs/Float64.h>



//Nodehandler object
ros::NodeHandle ntivac;

//Call back function where "tivac_msg" is message name.
void display_serial_data(const std_msgs::Float64 &tivac_msg)
{
  //Serial.print("tivac_msg");
  digitalWrite(30,HIGH);
  delay(500);
  digitalWrite(39,HIGH);
}

//Instantiate subscriber by mentioning topic which this node will suscribe to
ros::Subscriber<std_msgs::Float64> sub("/custom_numbers", &display_serial_data );
void setup() 
{ 
  
  //ALWAYS SET BAUD RATE BEFORE NODE INITIALIZATION.
  //nh.getHardware()->setBaud(115200);
  //.initNode() initialises node
  ntivac.initNode();
  
  ntivac.subscribe(sub); 

  pinMode(30,OUTPUT);
  pinMode(39,OUTPUT);
}

void loop() 
{
  ntivac.spinOnce();
  //delay(500); 
  
}
