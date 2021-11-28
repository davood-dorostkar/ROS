#ifndef __PLAN__
#define __PLAN__
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>
using namespace std;
ros::Publisher velocityCommand;
ros::Subscriber poseSensor;
turtlesim::Pose currentPosition;

class plan
{
private:
    const double PI = 3.14159265359;
    double now();
    void linearMove(double speed, double distance);
    void rotate(double angular_speed, double angle);
    double deg2rad(double degree);
    void goToAngle(double desiredAngle);
    void goToDestination(turtlesim::Pose goal, double distance_tolerance);
    double getDistance(double x1, double y1, double x2, double y2);

public:
    void updatePose(const turtlesim::Pose::ConstPtr &pose_msg);
    void path();
    plan();
    ~plan();
};

#endif