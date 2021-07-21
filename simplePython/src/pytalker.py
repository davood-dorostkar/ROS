#!/usr/bin/env python

import rospy
from std_msgs.msg import String


def talker():
    pubObject = rospy.Publisher("talker_topic", String, queue_size=10)
    rate = rospy.Rate(2)
    while not rospy.is_shutdown():
        rospy.loginfo("davood")
        pubObject.publish("davood")
        rate.sleep()


if __name__ == "__main__":
    rospy.init_node("talker_node")
    talker()
