#include "ros/ros.h"
#include "simpleService/multiply.h"

bool callBack(simpleService::multiply::Request &req,
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
  ros::NodeHandle node;

  ros::ServiceServer service = node.advertiseService("service_cpp", callBack);
  ROS_INFO("Ready...");
  ros::spin();

  return 0;
}
