#!/usr/bin/env python

import rospy
from messagesWithPython.msg import depth


def talker():
    rate = rospy.Rate(2)
    i = 1
    while not rospy.is_shutdown():
        depthMsg = depth()
        depthMsg.name = "davood"
        depthMsg.id = i
        depthMsg.x = i
        depthMsg.y = i
        rospy.loginfo("depth is: ")
        rospy.loginfo(depthMsg)
        pubObject.publish(depthMsg)
        i = i + 1
        rate.sleep()


if __name__ == "__main__":
    try:
        rospy.init_node("talker_node")
        pubObject = rospy.Publisher("talker_topic", depth, queue_size=10)
        talker()
    except:
        pass
