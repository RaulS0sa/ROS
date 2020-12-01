
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include <math.h> 
#define PI 3.14159265



int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "Objective");


  ros::NodeHandle n;

  ros::Publisher Publicador = n.advertise<turtlesim::Pose>("objetivo", 1000);
  ros::Rate loop_rate(10);
  while(ros::ok())
  {
  	turtlesim::Pose ObjectiveMessage;
  	ObjectiveMessage.x = 1;
  	ObjectiveMessage.y = 1;
	Publicador.publish(ObjectiveMessage);
	ros::spinOnce();
	loop_rate.sleep();
	
  }


  return 0;
}

