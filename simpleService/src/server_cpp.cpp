#include "ros/ros.h"
#include "simpleService/multiply.h"

bool multiple(simpleService::multiply::Request &req,
              simpleService::multiply::Response &res)
{
  res.sum = req.a * req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_cpp_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("service_cpp", multiple);
  ROS_INFO("Ready to multiple two ints.");
  ros::spin();

  return 0;
}
