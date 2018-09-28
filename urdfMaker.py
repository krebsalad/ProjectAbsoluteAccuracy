#!/usr/bin/env python

import os
import subprocess
import re
import sys
import glob
import getpass


# error messages
log = []


def print_log():
    if not log:
        print("No entries in log found.")
    else:
        for entry in log:
            print(entry)

# print help
def print_help():
    print("This is a script to create a project with urdf using ABB-metapackage abb and abb_experimental. The urdf will be ready to use with moveit setup assistant")
    print('Options: help/h/-h/options/opt, list_robots/list/l/list_packages, robot_name:=<irbXXX>, project_name:=<project_name>, ros_version:=<kinetic/indigo/>, abb_package:=<abb/abb_experimental>')
    print('Note: the robot name must be an existing abb robot in one of the following abb packages: abb or abb_experimental')


def print_robots():
    print("there are 2 abb packages: abb and abb_experimental")
    print('package abb has: irb2400, irb4400, irb5400, irb6600, irb6640' )
    print('package abb_experimental has: irb1200, irb120, irb1600, irb2600, irb4600, irb52, irb6650s, irb7600')


# startup arguments
sysarg_ros_version = "none"
sysarg_robot_name = "none"
sysarg_project_name = "none"
sysarg_project_folder_dir = "/home/"+getpass.getuser()+"/"
sysarg_abb_pkg = "none"

# help for options
if(len(sys.argv) == 1):
    print("Add atleast option robot_name:=<name>!")
    print_help()
    exit()

for arg in sys.argv:
    if(arg == "help" or arg == "h" or arg == "--h" or arg == "options" or arg == "opt"):
        print_help()
        exit()

    if(arg == "list_robots" or arg == "list" or arg == "l" or arg == "list_packages"):
        print_robots()
        exit()


# options
for arg in sys.argv:
    if(re.match("robot_name:=", arg)):
        sysarg_robot_name = re.sub("robot_name:=", "", arg)
    if(re.match("project_name:=", arg)):
        sysarg_project_name = re.sub("project_name:=", "", arg)
    if(re.match("ros_version:=", arg)):
        sysarg_ros_version = re.sub("ros_version:=", "", arg)
    if(re.match("abb_package:=", arg)):
        sysarg_abb_pkg = re.sub("abb_package:=", "", arg)

      
if(sysarg_abb_pkg != "abb" and sysarg_abb_pkg != "abb_experimental"):
    log.append("script does not work with package: "+sysarg_abb_pkg+", chose default: abb_experimental")
    sysarg_abb_pkg = "abb_experimental"

if (sysarg_robot_name == "none"):
    log.append("Please add a abb robot name. use option robot_name:=irbXXX, make sure its from the right abb package. do options list_robots")

if (sysarg_ros_version == "none"):
    if (os.path.exists("/opt/ros/"+"kinetic"+"/setup.bash")):
        log.append("No ros version was given, set to kinetic distribution because existing")
        sysarg_ros_version = "kinetic"
    else:
        if (os.path.exists("/opt/ros/"+"indigo"+"/setup.bash")):
            log.append("No ros version was given, tried kinetic but not existing, set to indigo distribution because existing")
            sysarg_ros_version = "indigo"
        else:
            erros.append("No ros distribution was given. Tried finding kinetic and indigo, both not existing! Make sure to add option ros_version:=<ros distribution name> on next run")
            print_log()
            exit()

if (sysarg_project_name == "none"):
    if not (os.path.exists(sysarg_project_folder_dir+"catkin_ws")):
        sysarg_project_name = "catkin_ws"
        log.append("project name not given, default name catkin_ws was chosen because was not existing")
    else:
        a = raw_input("default project name catkin_ws already exists, press y to create robot in this project, press any other key to cancel\n")
        if not (a == "y"):
            print_log()
            exit()
        else:
            log.append("project catkin_ws was chosen as default")
            sysarg_project_name = "catkin_ws"


# ROS args
arg_distribution_version = sysarg_ros_version
arg_ros_sources = 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
arg_keyp1 = 'hkp://ha.pool.sks-keyservers.net:80'
arg_keyp2 = '421C365BD9FF1F717815A3895523BAEEB01FA116'
arg_ros_distribution = "ros-"+arg_distribution_version+"-desktop-full"

# project args
arg_robot_package_name = "robot_"+sysarg_robot_name
arg_robot_support_package = "abb_"+sysarg_robot_name+"_support"
arg_abb_package = sysarg_abb_pkg

# project paths
pth_base = sysarg_project_folder_dir
pth_bashrc = pth_base+".bashrc"

pth_catkin_workspace = pth_base+sysarg_project_name+"/"
pth_project_packages = pth_catkin_workspace+"src/"
pth_pkg_robot = pth_project_packages+arg_robot_package_name+"/"

# ROS paths
pth_ros_distribution = "/opt/ros/"+arg_distribution_version+"/setup.bash"
pth_ros_downloads = pth_base+"ROS_Downloads/"

#download links
lnk_abb_git = "https://github.com/ros-industrial/abb.git"
lnk_abb_experimental_git = "https://github.com/ros-industrial/abb_experimental.git"
lnk_industrial_core_git = "https://github.com/ros-industrial/industrial_core.git"

# install ROS
if not (os.path.exists(pth_ros_distribution)):
    subprocess.call(["sudo", "sh", "-c", arg_ros_sources])
    subprocess.call(["sudo", "apt-key", "adv", "--keyserver", arg_keyp1, '--recv-key', arg_keyp2])
    subprocess.call(["sudo", "apt-get", "update"])
    subprocess.call(["sudo", "apt-get", "install", arg_ros_distribution])
    subprocess.call(["sudo", "rosdep", "init"])
    subprocess.call(["rosdep", "update"])
    subprocess.call(["echo", pth_ros_distribution, ">>", pth_bashrc])
else:
    log.append("ros-"+ arg_distribution_version+" already installed!")

# build project
subprocess.call(["mkdir", "-p", pth_project_packages])
subprocess.call(["catkin_init_workspace"], shell=True, cwd=pth_project_packages)
subprocess.call(["catkin_make"], shell=True, cwd=pth_catkin_workspace)

# downloading ros packages
subprocess.call(["mkdir", pth_ros_downloads])
if not (os.path.exists(pth_ros_downloads+"/abb")):
    subprocess.call(["git", "clone", lnk_abb_git, pth_ros_downloads+"/abb"])
else:
    log.append("meta-package abb already cloned")

if not (os.path.exists(pth_ros_downloads+"/abb_experimental")):
    subprocess.call(["git", "clone", lnk_abb_experimental_git, pth_ros_downloads+"/abb_experimental"])
else:
    log.append("meta-package abb_experimental already cloned")

if not (os.path.exists(pth_ros_downloads+"/industrial_core")):
    subprocess.call(["git", "clone", lnk_industrial_core_git, pth_ros_downloads+"/industrial_core"])
else:
    log.append("meta-package industrial_core already cloned")

# create package 
subprocess.call(["catkin_create_pkg", arg_robot_package_name, "roscpp"], cwd=pth_project_packages)
subprocess.call(["catkin_make"], shell=True, cwd=pth_catkin_workspace)

# subprocess.call(["mkdir", "-p", pth_pkg_robot+"src/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"config/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"launch/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"meshes/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"urdf/"])

# check if robot support package exists before trying to create urdf
if not (os.path.exists(pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package)):
    b = raw_input("Could not find package: "+ arg_robot_support_package+ " in "+arg_abb_package+" meta-package. Press y to try other meta package and any other key to cancel")
    if(b == "y"):
        if(arg_abb_package == "abb"):
            arg_abb_package = "abb_experimental"
        else:
            arg_abb_package = "abb"
        if not (os.path.exists(pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package)):
            log.append("could not find package: "+pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package+" to create robot urdf file with. Make sure the chosen robot exists. Use option list_robots to list robots in each package")
            print_log()
            exit()
        else:
            log.append("Changed package from abb to abb_experimental!")
    else:
        log.append("could not find package: "+pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package+" to create robot urdf file with. Make sure you have chosen the right abb metapackage or support package. Option abb_packkage:=<abb or abb_experimental>, use option list_robots to list robots in each package")
        print_log()
        exit()

# copy files for needed for the urdf to build a kinematic model
arg_macro_xacro = ""
for file in glob.glob(pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package+"/urdf/"+sysarg_robot_name+"*"+"_macro.xacro"):
    arg_macro_xacro = re.sub(pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package+"/urdf/", "", file)

subprocess.call(["cp", pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package+"/urdf/"+arg_macro_xacro, pth_pkg_robot+"urdf/"+arg_robot_package_name+".xacro"])
subprocess.call(["cp", "-r", pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package+"/meshes", pth_pkg_robot])
subprocess.call(["cp", "-r", pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_package+"/meshes", pth_pkg_robot])

# loop through each line in urdf and change/subsitute/remove uneeded xacro lines so that the xacro conversion to actual urdf can work
arg_abb_irb_name = re.sub("_macro.xacro", "", arg_macro_xacro)
with open(pth_pkg_robot+"urdf/"+arg_robot_package_name+".xacro") as f:
    urdf_file = open(pth_pkg_robot+"urdf/"+arg_robot_package_name+"_macro.urdf", "w+")
    for line in f:
        line = re.sub(arg_robot_support_package, arg_robot_package_name, line)
        line = re.sub('<xacro:macro name="'+arg_abb_irb_name+'" params="prefix">', "", line)
        line = re.sub('<robot xmlns:xacro=.*?>', '<robot name="'+arg_robot_package_name+'" xmlns:xacro="http://ros.org/wiki/xacro">', line)
        line = re.sub('<xacro:macro.*?>', "", line)
        line = re.sub('</xacro:macro>', "", line)
        line = re.sub('<xacro:include.*?>', "", line)
        line = re.sub('prefix', '',line)
        line = re.sub(r'[$]'+r'{}', '', line)
        line = re.sub('<xacro:material.*?>', '<material name="yellow">\n<color rgba="0 1 1 1"/>\n</material>', line)
        urdf_file.write(line)
    
    urdf_file.close()
    f.close()

# format from xacro to actual urdf
with open(pth_pkg_robot+"urdf/"+arg_robot_package_name+".urdf", "wb+", 0) as out:
   subprocess.call(['rosrun', 'xacro', 'xacro', pth_pkg_robot+"urdf/"+arg_robot_package_name+"_macro.urdf"], stdout=out)

# Rebuild project
subprocess.call(["catkin_make"], shell=True, cwd=pth_catkin_workspace)

# Done
print_log()
print("Succesfully run the script. This created a project: "+ sysarg_project_name +" with package: "+arg_robot_package_name+ " and urdf for "+arg_abb_irb_name+". The urdf is ready for MoveIT! setup assistant. Do not forget to source you project before using setupassistant, go into: "+pth_catkin_workspace+" and do: source devel/setup.bash")

# moveit setup assistant

# continu after moveit setup assistant with setting up for simulation