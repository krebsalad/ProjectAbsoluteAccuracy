#!/usr/bin/env python

import os
import subprocess
import re
import sys
import glob

# default startup arguments
sysarg_ros_version = "kinetic"
sysarg_robot_name = "irb1600"
sysarg_project_name = "catkin_ws"
sysarg_project_folder_dir = "/home/"+"turtle/"

# help for options
if(sys.argv[1] == "help"):
    print("Options: robot_name:=<name>, project_name:=<project_name>, ros_version:=<kinetic/indigo/>")

# options
for arg in sys.argv:
    if(re.match("robot_name:=", arg)):
        sysarg_robot_name = re.sub("robot_name:=", "", arg)
    if(re.match("project_name:=", arg)):
        sysarg_project_name = re.sub("project_name:=", "", arg)
    if(re.match("ros_version:=", arg)):
        sysarg_ros_version = re.sub("ros_version:=", "", arg)

# ROS args
arg_distribution_version = sysarg_ros_version
arg_ros_sources = 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
arg_keyp1 = 'hkp://ha.pool.sks-keyservers.net:80'
arg_keyp2 = '421C365BD9FF1F717815A3895523BAEEB01FA116'
arg_ros_distribution = "ros-"+arg_distribution_version+"-desktop-full"

# project args
arg_robot_package_name = "robot_"+sysarg_robot_name
arg_robot_support_package = "abb_"+sysarg_robot_name+"_support"

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
subprocess.call(["sudo", "sh", "-c", arg_ros_sources])
subprocess.call(["sudo", "apt-key", "adv", "--keyserver", arg_keyp1, '--recv-key', arg_keyp2])

subprocess.call(["sudo", "apt-get", "update"])
subprocess.call(["sudo", "apt-get", "install", arg_ros_distribution])

subprocess.call(["sudo", "rosdep", "init"])
subprocess.call(["rosdep", "update"])

subprocess.call(["echo", pth_ros_distribution, ">>", pth_bashrc])

# build project
subprocess.call(["mkdir", "-p", pth_project_packages])
subprocess.call(["catkin_init_workspace"], shell=True, cwd=pth_project_packages)
subprocess.call(["catkin_make"], shell=True, cwd=pth_catkin_workspace)

# downloading ros packages
subprocess.call(["mkdir", pth_ros_downloads])
subprocess.call(["git", "clone", lnk_abb_git, pth_ros_downloads+"/abb"])
subprocess.call(["git", "clone", lnk_abb_experimental_git, pth_ros_downloads+"/abb_experimental"])
subprocess.call(["git", "clone", lnk_industrial_core_git, pth_ros_downloads+"/industrial_core"])

# create package 
subprocess.call(["catkin_create_pkg", arg_robot_package_name, "roscpp"], cwd=pth_project_packages)
subprocess.call(["catkin_make"], shell=True, cwd=pth_catkin_workspace)

# subprocess.call(["mkdir", "-p", pth_pkg_robot+"src/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"config/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"launch/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"meshes/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"urdf/"])

# copy files for needed for the urdf to build a kinematic model
arg_macro_xacro = ""
for file in glob.glob(pth_ros_downloads+"abb_experimental/"+arg_robot_support_package+"/urdf/"+sysarg_robot_name+"*"+"_macro.xacro"):
    arg_macro_xacro = re.sub(pth_ros_downloads+"abb_experimental/"+arg_robot_support_package+"/urdf/", "", file)

subprocess.call(["cp", pth_ros_downloads+"abb_experimental/"+arg_robot_support_package+"/urdf/"+arg_macro_xacro, pth_pkg_robot+"urdf/"+arg_robot_package_name+".xacro"])
subprocess.call(["cp", "-r", pth_ros_downloads+"abb_experimental/"+arg_robot_support_package+"/meshes", pth_pkg_robot])
subprocess.call(["cp", "-r", pth_ros_downloads+"abb_experimental/"+arg_robot_support_package+"/meshes", pth_pkg_robot])

# loop through each line in urdf and change/subsitute/remove uneeded lines
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
print("done creating project "+arg_robot_package_name+ " with urdf for "+arg_abb_irb_name+". The urdf is ready for MoveIT! setup assistant. Do not forget to source you project before using setupassistant, go into: "+pth_catkin_workspace+" and do: source devel/setup.bash")