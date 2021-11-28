#include "ros/ros.h"
#include "simpleService/multiply.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_cpp_client");
  ros::NodeHandle node;
  ros::ServiceClient client = node.serviceClient<simpleService::multiply>("service_cpp");
  simpleService::multiply srv;
  srv.request.a = atoll(argv[1]);
  srv.request.b = atoll(argv[2]);
  if (client.call(srv))
  {
    ROS_INFO("multiple: %ld", (long int)srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed ");
    return 1;
  }

  return 0;
}