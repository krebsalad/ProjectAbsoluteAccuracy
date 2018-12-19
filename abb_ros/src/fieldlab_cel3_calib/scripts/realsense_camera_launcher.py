#!/usr/bin/env python

import os
import rospy
import subprocess
import sys
import re
import time
import roslaunch
import getpass
import signal


def launch_camera(camera_launch_file):
    uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
    roslaunch.configure_logging(uuid)
    launch = roslaunch.parent.ROSLaunchParent(uuid, [camera_launch_file])
    launch.start()
    rospy.loginfo("started")
    return launch


def reset_camera(vendor_id):
    path='/sys/bus/usb/devices/'

    sub_dirs = []
    for root, dirs, files in os.walk(path):
            for name in dirs:
                    sub_dirs.append(os.path.join(root, name))

    dev_found = 0
    for sub_dir in sub_dirs:
            if True == os.path.isfile(sub_dir+'/devnum'):
                    if True == os.path.isfile(sub_dir+'/idVendor'):
                        with open(sub_dir+'/idVendor', 'r') as f:
                            for line in f:
                                line = str.format(line)
                                line = re.sub("\n", "", line)
                                if(str(line) == str(vendor_id)):
                                    dev_found = 1
                                    print("found device at: "+ sub_dir + "/devnum")
                                    break
                        if(dev_found == 1):
                            break

    if dev_found == 1:
        reset_file = sub_dir+'/authorized'
        subprocess.call(['sudo', 'bash', '-c', "echo 0 > '"+sub_dir+"/authorized'"])
        time.sleep(3)
        subprocess.call(['sudo', 'bash', '-c', "echo 1 > '"+sub_dir+"/authorized'"])
        time.sleep(1)
        print ("succesfully reset device")
    else:
        print ("No such device")
        return False
    return True


def signal_handler(sig, frame):
    sys.exit(0)


def main():
    # init rospy
    rospy.init_node('camera_launcher', anonymous=True)

    # arguments !!!!! CHANGE depending on camera and launch file
    vendor_id = "8086"
    base_path = "/home/"+getpass.getuser()+"/"
    launch_file = base_path + 'abb_ros/src/realsense2_camera/launch/rs_rgbd.launch'

    # replug camera
    if(sys.argv[1]):
        if(sys.argv[1] == "replug"):
            if not (reset_camera(vendor_id)):
                print("could not reset device with vendor id: "+vendor_id+", please make sure this vendor_id is equal to the said camera")
    
    # launch camera
    if (os.path.exists(launch_file)):
        launch_process = launch_camera(launch_file)
        # wait for ctrl + c
        signal.signal(signal.SIGINT, signal_handler)
        signal.pause()
        launch.shutdown()
        print("shutting down")
    else:
        print("could not find launch file: "+launch_file)

if __name__ == "__main__":
    main()
    exit()
