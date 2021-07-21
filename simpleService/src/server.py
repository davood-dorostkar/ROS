#!/usr/bin/env python

import rospy
from service.srv import service


def multiplyCallBack(input):
    result = input.a * input.b
    rospy.loginfo(
        "\ninput: [%s,%s]"
        % (
            input.a,
            input.b,
        )
        + "\nresult: %s" % result,
    )
    return result


def multiply_service():
    rospy.Service("multiply_service", service, multiplyCallBack)
    rospy.spin()


if __name__ == "__main__":
    rospy.init_node("multiply_server_node")
    multiply_service()
