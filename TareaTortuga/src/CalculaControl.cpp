#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "turtlesim/Pose.h"
#include <TareaTortuga/cmd_velmsg.h>
#include <math.h> 
#define PI 3.14159265
#define K_Gain -.45
typedef struct Posicion
{
	double x;
	double y;
	double theta;
}Posicion;
ros::Publisher Publicador;
Posicion Pose;
Posicion Objetivo;



void PoseSubscribeallback(const turtlesim::Pose::ConstPtr& msg)
{
Pose.x = msg->x;
Pose.y = msg->y;
Pose.theta = msg->theta;

}

void ObjectivoSubscribeallback(const turtlesim::Pose::ConstPtr& msg)
{
Objetivo.x = msg->x;
Objetivo.y = msg->y;
Objetivo.theta = 0;

}


int distance(int alpha, int beta) {
        int phi = abs(beta - alpha) % 360;
        int distance = phi > 180 ? 360 - phi : phi;
        return distance;
 }

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "CalculateControl");
  ros::NodeHandle n; 
  ros::Subscriber PoseSubscribe = n.subscribe("/turtle1/pose", 1000, PoseSubscribeallback);
  ros::Subscriber ObjetivoSubscribe = n.subscribe("objetivo", 1000, ObjectivoSubscribeallback);
   ros::Publisher Publicador = n.advertise<std_msgs::Float64>("Omega", 1000);
  ros::Rate loop_rate(10);
  while(ros::ok())
  {
  	 double errorX =  Objetivo.x -Pose.x;
        double errorY =  Objetivo.y-Pose.y ;
        double ref = atan2(errorY,errorX);
        double omega = K_Gain * (((double)(distance((int)(Pose.theta* 180 / PI), ref * 180 / PI))) / 57.0);

        std_msgs::Float64 AnguloMensaje;
        AnguloMensaje.data = omega;
        Publicador.publish(AnguloMensaje);
        
        
          ROS_INFO("ref: [%f], Pose.theta: [%f], omega: [%f],", ref,Pose.theta, omega);
        ros::spinOnce();
        loop_rate.sleep();
	
  }


  return 0;
}



