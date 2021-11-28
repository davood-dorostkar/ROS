#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
using namespace std;
ros::Publisher turtlePublisher;

double now()
{
    return ros::Time::now().toSec();
}

void move(double desiredDistance, double desiredSpeed)
{
    ros::Rate loopRate(50);
    geometry_msgs::Twist drive_msg;
    double currentDistance = 0;
    double startTime = now();
    if (currentDistance < desiredDistance)
    {
        drive_msg.linear.x = desiredSpeed;
        drive_msg.linear.y = 0;
        drive_msg.linear.z = 0;
        drive_msg.angular.x = 0;
        drive_msg.angular.y = 0;
        drive_msg.angular.z = 0;
        turtlePublisher.publish(drive_msg);
        currentDistance = (now() - startTime) * desiredSpeed;
        loopRate.sleep();
    }
    else
    {
        drive_msg.linear.x = 0;
        turtlePublisher.publish(drive_msg);
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "driver");
    ros::NodeHandle node;
    turtlePublisher = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    double desiredDistance, desiredSpeed;
    while (true)
    {
        cout << "enter distance:\n";
        cin >> desiredDistance;
        cout << "enter speed:\n";
        cin >> desiredSpeed;
        move(desiredDistance, desiredSpeed);
        ros::spin();
    }
}