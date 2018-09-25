#!/usr/bin/env python

import os
import subprocess
import re

# ROS args
arg_distribution_version = "kinetic"
arg_ros_sources = 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
arg_keyp1 = 'hkp://ha.pool.sks-keyservers.net:80'
arg_keyp2 = '421C365BD9FF1F717815A3895523BAEEB01FA116'
arg_ros_distribution = "ros-"+arg_distribution_version+"-desktop-full"

# project args
arg_robot_package_name = "robot_irb1600"

# project paths
pth_base = "/home/turtle/"
pth_bashrc = pth_base+".bashrc"

pth_catkin_workspace = pth_base+"catkin_ws/"
pth_project_packages = pth_base+"catkin_ws/src/"
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

# create package (create pkg not yet working)
subprocess.call(["catkin_create_pkg", arg_robot_package_name, "roscpp"], cwd=pth_project_packages)
subprocess.call(["catkin_make"], shell=True, cwd=pth_catkin_workspace)

subprocess.call(["mkdir", "-p", pth_pkg_robot+"src/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"config/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"launch/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"meshes/"])
subprocess.call(["mkdir", "-p", pth_pkg_robot+"urdf/"])

# copy files for needed for the urdf to build a kinematic model
subprocess.call(["cp", pth_ros_downloads+"abb_experimental/abb_irb1600_support/urdf/irb1600_6_12_macro.xacro", pth_pkg_robot+"urdf/"+arg_robot_package_name+".xacro"])
subprocess.call(["cp", "-r", pth_ros_downloads+"abb_experimental/abb_irb1600_support/meshes/irb1600", pth_pkg_robot+"meshes/"])
subprocess.call(["cp", "-r", pth_ros_downloads+"abb_experimental/abb_irb1600_support/meshes/irb1600_6_12", pth_pkg_robot+"meshes/"])

# loop through each line in urdf and change/subsitute/remove uneeded lines
with open(pth_pkg_robot+"urdf/"+arg_robot_package_name+".xacro") as f:
    urdf_file = open(pth_pkg_robot+"urdf/"+arg_robot_package_name+"_macro.urdf", "w+")
    for line in f:
        line = re.sub(r'\babb_irb1600_support\b', arg_robot_package_name, line)
        line = re.sub('<xacro:macro name="abb_irb1600_6_12" params="prefix">', "", line)
        line = re.sub('<robot xmlns:xacro="http://ros.org/wiki/xacro" name="irb1600_6_12">', '<robot name="'+arg_robot_package_name+'" xmlns:xacro="http://ros.org/wiki/xacro">', line)
        line = re.sub('</xacro:macro>', "", line)
        line = re.sub('prefix', '',line)
        line = re.sub(r'[$]'+r'{}', '', line)
        urdf_file.write(line)
    
    urdf_file.close()
    f.close()

# format from xacro to actual urdf
with open(pth_pkg_robot+"urdf/"+arg_robot_package_name+".urdf", "wb+", 0) as out:
   subprocess.call(['rosrun', 'xacro', 'xacro', pth_pkg_robot+"urdf/"+arg_robot_package_name+"_macro.urdf"], stdout=out)

# Rebuild project
subprocess.call(["catkin_make"], shell=True, cwd=pth_catkin_workspace)

# Done