#!/usr/bin/env python

import threading
import rospy
import tf
from panels import NewActionModulation
from Tkinter import Tk
from theatre_bot.msg import EmotionMessage
from theatre_bot.srv import *
from std_msgs.msg import String,Char

from ttk import Frame

"""
this interface is to test the action modulation system.
it show de current possition of the robot, the velocity.
it could be used to send a set of emotions and actions. 
the parameters that could be send to the module are position and velocity.

The button stop just stop the platform not the module, thus the robot
will continue moving even if this button was pressed because the module will 
continue sending messages to the platform.

To resolved this problem the button abort was added, which sends to the module
the action not_do_anything and then sends the message to the platform to stop.

To add new actions and emotions has to be changed the file ./panels/ActionModulation.py
"""
def interface_test_action_modulation():
        global app
        root = Tk()
        app = NewActionModulation.NewActionModulation(root)
        rospy.init_node('interface_test_action_modulation', anonymous=True)
        #pubNewAction = rospy.Publisher('/change_action',ActionDesireMessage,queue_size=10)
        pubNewEmotion = rospy.Publisher('/change_emotion',EmotionMessage, queue_size=10)
        app.getButtonSendEmotion().configure(command= lambda: pub_information_emotion(pubNewEmotion))
        app.getButtonSendAction().configure(command= lambda: pub_information_action())
        app.getButtonStop().configure(command= lambda: pub_stop())
        """pubCommand = rospy.Publisher('commands_triskar',Char,queue_size=10)
        rospy.Subscriber("odometry_triskar", OdometryTriskar, callback)
        app.getButtonAbort().configure(command = lambda: pub_abort(pubCommand,pubNewAction,pubNewEmotion))
        app.getButtonReset().configure(command= lambda: pub_reset(pubCommand))
        """
        root.mainloop()
        
def callback(data):
    app.getPanelInfoPosition().setInfo(data.pose.position.x,data.pose.position.y,data.pose.orientation)
    app.getPanelInfoVelocity().setInfo(data.twist.linear.x,data.twist.linear.y,data.twist.angular)
    
"""def pub_abort(pubCommand,pubNewAction,pubNewEmotion):
    #send the stop to the subsystem
    """

def pub_information_emotion(pubNewEmotion):
    print 'send emotion'
    message = EmotionMessage()
    message.emotion.data = app.getFirstTab().getListEmotion()
    message.intensity.data = float(app.getFirstTab().getIntensity())
    pubNewEmotion.publish(message)
    

def pub_information_action():
    #print ('send action', app.getCurrentTab())
    if app.getCurrentTab() == 0:
        action = app.getFirstTab().getListAction()
        positionX, positionY, positionZ = app.getFirstTab().getPanelPosition().getInfo()
        othersX,othersY,othersZ = app.getFirstTab().getPanelVelocity().getInfo()
        message = '{ "is_primary"    :    "yes", "type" :'
        if action == "walk":
            message += '"composite_action", "name" : "walk", "parameters" : ['
            message += '{ "type" : "mandatory_parameter", "name"        :    "parameter_point_body", '
            if othersZ != 0:
                quaternion = tf.transformations.quaternion_from_euler(0, 0, float(othersZ))
                message += '"pose" : ['
                message += str(quaternion[0])
                message += ','
                message += str(quaternion[1])
                message += ','
                message += str(quaternion[2])
                message += ','
                message += str(quaternion[3])
                message += '],'
            message += '"point" : ['
            message +=  positionX
            message += ','
            message += positionY
            message += ','
            message += positionZ
            message += ']},'
            message += '{ "type" : "mandatory_parameter", "name"        :    "parameter_amplitude_shoulder", "amplitude" : ['
            message += othersX
            message += ',0,0]},'
            message += '{ "type" : "mandatory_parameter", "name"        :    "parameter_amplitude_torso", "amplitude" : ['
            message += othersY
            message += ',0,0]}'
            message += ']'
        elif action == "not_do_anything" :
            message +=   '"simple_action", "name" : "do_nothing"'
            message += ', "parameters" : [{ "type": "mandatory_parameter","name": "parameter_time", "time":' 
            message +=  positionX     
            message += '}]'
        else:
            message += '"simple_action", "name" : "'
            message += app.getFirstTab().getListAction()
            message += '", "parameters" : [{ "type": "mandatory_parameter","name":'
            if app.getFirstTab().getListAction() == 'move_body':
                message+= '"parameter_point",'
                if othersZ != 0:
                    quaternion = tf.transformations.quaternion_from_euler(0, 0, float(othersZ))
                    message += '"pose" : ['
                    message += str(quaternion[0])
                    message += ','
                    message += str(quaternion[1])
                    message += ','
                    message += str(quaternion[2])
                    message += ','
                    message += str(quaternion[3])
                    message += '],'
                    message += '"point" : ['
            else:
                message += '"parameter_amplitude","amplitude" : ['
            message +=  positionX
            message += ','
            message += positionY
            message += ','
            message += positionZ
            message += ']}]'
        message += '}'
        print 'tab 1'
    elif app.getCurrentTab() == 1:
        message = app.getSecondTab().getText()
        print 'tab 2'
    print message
    #Sending the messsage
    rospy.wait_for_service('change_action')
    try:
        action_service = rospy.ServiceProxy('change_action',ActionService)
        resp1 = action_service(message)
        print resp1.response
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def pub_stop():    
    message = "stop"
    #Sending the messsage
    rospy.wait_for_service('change_action')
    try:
        action_service = rospy.ServiceProxy('change_action',ActionService)
        resp1 = action_service(message)
        print resp1.response
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e
    
"""def pub_stop(pubCommand):    
    print 'stop'
    str = 83
    pubCommand.publish(str)

def pub_reset(pubCommand):
    print 'reset'
    str = 82
    pubCommand.publish(str)"""
    
    
if __name__ == '__main__':
    try:
        interface = interface_test_action_modulation()
    except rospy.ROSInterruptException: pass
