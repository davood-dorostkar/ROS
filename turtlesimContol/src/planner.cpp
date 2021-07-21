#include "plan.h"
plan route;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "planner");
    ros::NodeHandle node;
    velocityCommand = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    poseSensor = node.subscribe("/turtle1/pose", 10, route.updatePose);
    ros::Rate loop(0.5);
    route.path();
    ros::spin();
    return 0;
}