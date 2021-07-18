#!/usr/bin/env python

import rospy
from pkg1.msg import depth


def talker():
    pubObject = rospy.Publisher("talker_topic", depth, queue_size=10)
    rospy.init_node("talker_node")
    rate = rospy.Rate(2)
    i = 1

    while not rospy.is_shutdown():
        depthMsg = depth()
        depthMsg.id = i
        depthMsg.name = "davood"
        depthMsg.x = i
        depthMsg.y = i
        rospy.loginfo("depth is: ")
        rospy.loginfo(depthMsg)
        pubObject.publish(depthMsg)
        i = i + 1
        rate.sleep()


if __name__ == "__main__":
    try:
        talker()
    except:
        pass
