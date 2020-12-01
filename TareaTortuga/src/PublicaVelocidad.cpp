
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "turtlesim/Pose.h"
#include <TareaTortuga/cmd_velmsg.h>
#include <math.h> 
#include <geometry_msgs/Twist.h>
#define PI 3.14159265

//ros::Publisher Publicador;
float Lin_vel=0;
float Ang_vel=0;
void linVelCallback(const std_msgs::Float64::ConstPtr& msg)
{

    Lin_vel = static_cast<float>(msg->data);
    //PublicaResultados();

}

void AngVelCallback(const std_msgs::Float64::ConstPtr& msg)
{
	ROS_INFO("Ang_vel: [%f]", msg->data);
    Ang_vel =static_cast<float>(msg->data);
   // PublicaResultados();
 
}

void PublicaResultados()
{
  
}




int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "PublishSpeed");


  ros::NodeHandle n;

 
  ros::Subscriber PoseSubscribe = n.subscribe("linear_vel", 1000, linVelCallback);
  ros::Subscriber ObjetivoSubscribe = n.subscribe("Omega", 1000, AngVelCallback);
  //Publicador = n.advertise<msgs::cmd_velmsg>("cmd_vel", 1000);
  //ros::spin();
   ros::Publisher Publicador = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
  ros::Rate loop_rate(10);
  while(ros::ok())
  {
  	  //if(Pose != null && Objetivo!= null)
	  //  {
	       //TareaTortuga::cmd_velmsg respuesta;// = new TareaTortuga::cmd_velmsg();
	       //respuesta.linear_vel = Lin_vel;
	       //respuesta.angular_vel = Ang_vel;
	//	Publicador.publish(respuesta);
	  //  }
	  	ROS_INFO("Lin_vel: [%f]", Lin_vel);
	  		  	ROS_INFO("Ang_vel: [%f]", Ang_vel);
	geometry_msgs::Twist twist;
    twist.angular.z = Ang_vel;
    twist.linear.x = Lin_vel;
    Publicador.publish(twist);
     ros::spinOnce();
        loop_rate.sleep();
	
  }


  return 0;
}

