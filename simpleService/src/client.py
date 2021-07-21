#!/usr/bin/env python

import rospy
import sys
from service.srv import service


def multiply_client(a, b):
    rospy.wait_for_service("multiply_service")
    try:
        clientSend = rospy.ServiceProxy("multiply_service", service)
        request = clientSend(a, b)
        print("%s * %s= %s" % (a, b, request.sum))
        return request.sum

    except rospy.ServiceException as e:
        print("fail")


if __name__ == "__main__":
    a = int(sys.argv[1])
    b = int(sys.argv[2])
    multiply_client(a, b)
