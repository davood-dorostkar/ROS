#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>
using namespace std;
ros::Publisher velocityCommand;
ros::Subscriber poseSensor;
turtlesim::Pose currentPosition;
const double PI = 3.14159265359;

double now();
void linearMove(double speed, double distance);
void rotate(double angular_speed, double angle);
double deg2rad(double degree);
void goToAngle(double desiredAngle);
void goToDestination(turtlesim::Pose goal, double distance_tolerance);
void updatePose(const turtlesim::Pose::ConstPtr &pose_msg);
void plan();

int main(int argc, char **argv)
{
    ros::init(argc, argv, "planner");
    ros::NodeHandle node;
    velocityCommand = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    poseSensor = node.subscribe("/turtle1/pose", 10, updatePose);
    ros::Rate loop(0.5);
    plan();
    ros::spin();
    return 0;
}

double now()
{
    return ros::Time::now().toSec();
}

void linearMove(double speed, double distance)
{
    geometry_msgs::Twist velocity_msg;
    velocity_msg.linear.x = speed;
    velocity_msg.linear.y = 0;
    velocity_msg.linear.z = 0;
    velocity_msg.angular.x = 0;
    velocity_msg.angular.y = 0;
    velocity_msg.angular.z = 0;

    double current_distance = 0.0;
    ros::Rate loop(1000);
    double t0 = now();
    do
    {
        velocityCommand.publish(velocity_msg);
        double t1 = now();
        current_distance = speed * (t1 - t0);
        ros::spinOnce();
        loop.sleep();
    } while (current_distance < distance);
    velocity_msg.linear.x = 0;
    velocityCommand.publish(velocity_msg);
}

void rotate(double angular_speed, double relative_angle)
{

    geometry_msgs::Twist velocity_msg;
    velocity_msg.linear.x = 0;
    velocity_msg.linear.y = 0;
    velocity_msg.linear.z = 0;
    velocity_msg.angular.x = 0;
    velocity_msg.angular.y = 0;
    if (relative_angle > 0)
        velocity_msg.angular.z = angular_speed;
    else
        velocity_msg.angular.z = -angular_speed;

    double current_angle = 0.0;
    double t0 = now();
    ros::Rate loop(100);
    do
    {
        velocityCommand.publish(velocity_msg);
        double t1 = now();
        current_angle = angular_speed * (t1 - t0);
        ros::spinOnce();
        loop.sleep();
    } while (abs(current_angle) < abs(relative_angle));

    velocity_msg.angular.z = 0;
    velocityCommand.publish(velocity_msg);
}

double deg2rad(double degree)
{
    return degree * PI / 180.0;
}

void goToAngle(double desiredAngle)
{
    double difference = desiredAngle - currentPosition.theta;
    rotate(deg2rad(10), difference);
}

void updatePose(const turtlesim::Pose::ConstPtr &pose_msg)
{
    currentPosition.x = pose_msg->x;
    currentPosition.y = pose_msg->y;
    currentPosition.theta = pose_msg->theta;
}

double getDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

void goToDestination(turtlesim::Pose goal, double distance_tolerance)
{

    geometry_msgs::Twist velocity_msg;
    ros::Rate loop(100);
    do
    {
        double e = getDistance(currentPosition.x, currentPosition.y, goal.x, goal.y);
        velocity_msg.linear.x = 0.5 * e;
        velocity_msg.linear.y = 0;
        velocity_msg.linear.z = 0;
        velocity_msg.angular.x = 0;
        velocity_msg.angular.y = 0;
        velocity_msg.angular.z = 4 * (atan2(goal.y - currentPosition.y, goal.x - currentPosition.x) - currentPosition.theta);
        velocityCommand.publish(velocity_msg);
        ros::spinOnce();
        loop.sleep();

    } while (getDistance(currentPosition.x, currentPosition.y, goal.x, goal.y) > distance_tolerance);
    cout << "Goal accomplished" << endl;
    velocity_msg.linear.x = 0;
    velocity_msg.angular.z = 0;
    velocityCommand.publish(velocity_msg);
}

void plan()
{
    /// PART 1 ///
    ros::Rate loop(100);
    turtlesim::Pose pose;
    cout << "Enter initial x: " << endl;
    cin >> pose.x;
    cout << "Enter initial y: " << endl;
    cin >> pose.y;
    goToDestination(pose, 0.01);
    loop.sleep();

    /// PART 2 ///
    pose.x = 0;
    pose.y = 0;
    pose.theta = 0;
    goToDestination(pose, 0.01);
    loop.sleep();

    /// PART 3 ///
    goToAngle(deg2rad(45));
    loop.sleep();

    /// PART 4 ///
    pose.x = 5.5;
    pose.y = 5.5;
    pose.theta = 0;
    goToDestination(pose, 0.01);
    loop.sleep();
    cout << currentPosition.theta << endl;
    goToAngle(0);
    loop.sleep();

    /// PART 5 ///
    double x = 1.0;
    for (int i = 0; i < 12; i++)
    {
        ros::Rate loop(100);
        if (i != 0 && i % 2 == 0)
            x++;
        cout << x << endl;
        linearMove(2.0, x);
        loop.sleep();
        rotate(deg2rad(10), deg2rad(90));
        loop.sleep();
    }

    /// PART 6 ///
    geometry_msgs::Twist velocity_msg;
    goToAngle(0);
    do
    {
        double distance = getDistance(currentPosition.x, currentPosition.y, 5.5, 5.5);
        // double constSpeed = 1.0;
        double beta = atan2(currentPosition.y - 5.5, currentPosition.x - 5.5);
        double gama = currentPosition.theta;
        double e = beta + gama - PI / 2;
        velocity_msg.linear.x = distance;
        velocity_msg.linear.y = 0;
        velocity_msg.linear.z = 0;
        velocity_msg.angular.x = 0;
        velocity_msg.angular.y = 0;
        velocity_msg.angular.z = -1.0 * e;
        velocityCommand.publish(velocity_msg);
        ros::spinOnce();
    } while (getDistance(currentPosition.x, currentPosition.y, 5.5, 5.5) > 0.01);
    loop.sleep();
}