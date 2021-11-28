#!/usr/bin/env python

import rospy
from std_msgs.msg import String


def reaction(msg):
    rospy.loginfo("I got this: %s", msg)


def listener():
    subObject = rospy.Subscriber("talker_topic", String, reaction)
    rospy.spin()


if __name__ == "__main__":
    rospy.init_node("listener_node")
    listener()
