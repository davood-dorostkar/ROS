#!/usr/bin/env python

import rospy
from messagesWithPython.msg import depth


def reaction(msg):
    rospy.loginfo("I got this: %d, %s, %2f, %2f", msg.id, msg.name, msg.x, msg.y)


def listener():
    subObject = rospy.Subscriber("talker_topic", depth, reaction)
    rospy.init_node("listener_node")
    rospy.spin()


if __name__ == "__main__":
    try:
        listener()
    except:
        pass
