
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "turtlesim/Pose.h"
#include <TareaTortuga/cmd_velmsg.h>
#include <math.h> 
#define PI 3.14159265
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
int main(int argc, char **argv)
{

  ros::init(argc, argv, "LinVel");

  ros::NodeHandle n;
 
  ros::Subscriber PoseSubscribe = n.subscribe("/turtle1/pose", 1000, PoseSubscribeallback);
  ros::Subscriber ObjetivoSubscribe = n.subscribe("objetivo", 1000, ObjectivoSubscribeallback);
  Publicador = n.advertise<std_msgs::Float64>("linear_vel", 1000);
  ros::Rate loop_rate(10);

  //int count = 0;
  while (ros::ok())
  {

    //if(Pose != null && Objetivo!= null)
    //{
        double errorX = Pose.x - Objetivo.x;
        double errorY = Pose.y - Objetivo.y;
        double Distancia = sqrt((errorX*errorX) + (errorY*errorY));
        std_msgs::Float64 Disc;// = new std_msgs::Float64();
        Disc.data = Distancia < 0.2 ? 0 : Distancia*0.2;
        
        
        ROS_INFO("Posex: [%f], Posey: [%f], ObjetivoX: [%f], errorX: [%f], errorY: [%f], Distancia: [%f]", Pose.x,Pose.y, Objetivo.x,errorX,errorY,Distancia );
        Publicador.publish(Disc);
       //   chatter_pub.publish(msg);
    //}

  

    ros::spinOnce();
        loop_rate.sleep();

    //loop_rate.sleep();
    //++count;
  }


  return 0;
}
// %EndTag(FULLTEXT)%
