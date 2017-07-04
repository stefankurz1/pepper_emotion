#!/usr/bin/env python

import threading
import rospy
import Queue
from panels import ActionModulationTest
from Tkinter import Tk
from theatrebot_action_modulation.msg import ActionDesireMessage
from std_msgs.msg import String

from ttk import Frame

class interface_test_action_modulation():
    def __init__(self):
        info_queue = Queue.Queue()
        data_queue = Queue.Queue()
        rospy.init_node('interface_test_action_modulation', anonymous=True)
        pubNewAction = rospy.Publisher('new_action',ActionDesireMessage,queue_size=1)
        pubNewEmotion = rospy.Publisher('new_emotion',String,queue_size=1)
    
        app = ActionModulationTest.ActionModulationTest(info_queue,data_queue)
        app.start()
        rospy.spin()
        app.join()
    
    
    def pub_information():
        print 'send info'    
if __name__ == '__main__':
    try:
        interface = interface_test_action_modulation()
    except rospy.ROSInterruptException: pass