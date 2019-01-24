#!/usr/bin/env python

import rospy
import roslib; roslib.load_manifest('urdfdom_py')

from urdf_parser_py.urdf import URDF

joint_names = rospy.get_param('/controller_joint_names', [])

if not (joint_names):
    print("joint_offset load: could not find /controller_joint_names")
    exit()

joint_offsets = []

robot = URDF.from_parameter_server()

if not (robot):
    print("joint_offset load: could not load urdf ")
    exit()

for name in joint_names:
    if(robot.joint_map[name]):
        if (robot.joint_map[name].calibration):
            joint_offsets.append( robot.joint_map[name].calibration.rising)
        else:
            joint_offsets.append(0)
    else:
        print("joint_offset load: could not find joint named " + name + " in robot description")

if not (joint_offsets):
    print("joint_offset load: no joint_offsets were found")
    exit()

rospy.set_param('/controller_joint_offsets', joint_offsets)
