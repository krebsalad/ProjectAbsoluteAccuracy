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

    # arguments
    vendor_id = "8086"
    base_path = '/home/'+getpass.getuser()+'/'

    # roslaunch camera arguments
    launch_file_package = "fieldlab_cel3_calib"
    launch_file_name = "cameras_cal.launch"
    launch_file_path = base_path + 'abb_ros/src/' + launch_file_package + '/launch/' + launch_file_name

    # replug camera
    if(sys.argv[1]):
        if(sys.argv[1] == "replug"):
            if not (reset_camera(vendor_id)):
                print("could not reset device")
    
    # launch camera
    if (os.path.exists(launch_file_path)):
        # init roslaunch
        uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(uuid)

        # launch file
        launch = roslaunch.parent.ROSLaunchParent(uuid, [launch_file_path])

        # start
        launch.start()
        print("starting camera nodes...")

        # wait for ctrl + c
        signal.signal(signal.SIGINT, signal_handler)
        signal.pause()

        # shutdown
        print("shutting down camera nodes...")
        launch.stop()

    else:
        print("could not find launch file: "+ launch_file_path)


if __name__ == "__main__":
    main()
    exit()
