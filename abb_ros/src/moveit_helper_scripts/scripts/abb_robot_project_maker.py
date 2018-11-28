#!/usr/bin/env python

import os       
import subprocess
import re
import sys
import glob
import getpass

# list with logs
log = []

# print log list
def print_log():
    print("\n Project Maker Script Log and Error list:")
    if not log:
        print("No entries in script log found.")
    else:
        count = 0
        for entry in log:
            count += 1
            print("\n"+str(count)+") "+entry)

# print help
def print_help():
    print("\nI. This is a script to create a project with robot specific packages using ABB-metapackages abb and abb_experimental. The urdf of the robot will be ready to use with moveit setup assistant")
    print('\nII. Options: help/h/-h/options/opt, list_robots/list/l/list_packages, robot_name:=<irbXXX>, project_name:=<project_name>, ros_version:=<kinetic/indigo/>, abb_package:=<abb/abb_experimental>')
    print('\nIII. run the script with atleast option robot_name:=<irbxxx>. Default project directory is catkin_ws. The abb packages will automatically be switched if the robot can not be found')
    print('\nNote: the robot name must be an existing abb robot in one of the following abb packages: abb or abb_experimental. The script is reusable on the same package or different package in same project')


# print available abb robots
def print_robots():
    print("there are 2 abb packages: abb and abb_experimental")
    print('package abb has: irb2400, irb4400, irb5400, irb6600, irb6640' )
    print('package abb_experimental has: irb1200, irb120, irb1600, irb2600, irb4600, irb52, irb6650s, irb7600')

# create new directory
def create_directory_if_not_existing(dir_path):
    if not (os.path.exists(dir_path)):
        subprocess.call(["mkdir", "-p", dir_path])
    else:
        log.append("did not create directory "+dir_path+", because already existing")


# copy file/dir to dir
def copy_dir_to_dir(dir_path1, dir_path2):
    if (os.path.exists(dir_path1)):
        if (os.path.exists(dir_path2)):
            subprocess.call(["cp", "-r", dir_path1, dir_path2])
        else:
            log.append(dir_path2 + "not existing!!")
    else:
        log.append(dir_path1 + "not existing!!")


# startup arguments
sysarg_ros_version = "none"
sysarg_robot_name = "none"
sysarg_project_name = "none"
sysarg_project_folder_dir = "/home/"+getpass.getuser()+"/"
sysarg_abb_meta_pkg = "none"

# auto help if no option
if(len(sys.argv) == 1):
    print("Add atleast option robot_name:=<name>!")
    print_help()
    exit()

# help options
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
        sysarg_abb_meta_pkg = re.sub("abb_package:=", "", arg)

# check if package existing, else change to exsting
if(sysarg_abb_meta_pkg != "abb" and sysarg_abb_meta_pkg != "abb_experimental"):
    log.append("script does not work with package: "+sysarg_abb_meta_pkg+", chose default: abb_experimental")
    sysarg_abb_meta_pkg = "abb_experimental"

# check if robot name was given
if (sysarg_robot_name == "none"):
    log.append("\nFAILED Please add a abb robot name. use option robot_name:=irbXXX, make sure its from the right abb package. do option list\n")
    exit()

# ros version only indigo and kinetic!!
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

# check if project name given
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
arg_robot_package_name = "abb_"+sysarg_robot_name+"_moveit_config"
arg_robot_support_name= "abb_"+sysarg_robot_name+"_support"
arg_abb_package = sysarg_abb_meta_pkg

# standard paths
pth_base = sysarg_project_folder_dir
pth_bashrc = pth_base+".bashrc"

# ROS paths
pth_ros_distribution = "/opt/ros/"+arg_distribution_version+"/setup.bash"
pth_ros_downloads = pth_base+"ROS_Downloads/"

# Project paths
pth_catkin_workspace = pth_base+sysarg_project_name+"/"
pth_project_packages = pth_catkin_workspace+"src/"
pth_pkg_config = pth_project_packages+arg_robot_package_name+"/"
pth_pkg_support = pth_project_packages+arg_robot_support_name+"/"
pth_origin_pkg_config = pth_ros_downloads+arg_abb_package+"/"+arg_robot_package_name+"/"
pth_origin_pkg_support = pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_name+"/"

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

# download ros packages
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

# check if robot support package exists before trying to create urdf
if not (os.path.exists(pth_origin_pkg_support)):
    b = raw_input("Could not find package: "+ arg_robot_support_name+ " in "+arg_abb_package+" meta-package. Press y to try other meta package and any other key to cancel")
    if(b == "y"):
        if(arg_abb_package == "abb"):
            arg_abb_package = "abb_experimental"
        else:
            arg_abb_package = "abb"
        if not (os.path.exists(pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_name)):
            log.append("could not find package: "+pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_name+" to create robot urdf file with. Make sure the chosen robot exists. Use option list_robots to list robots in each package")
            print_log()
            exit()
        else:
            log.append("Changed abb meta package to the other one")
    else:
        log.append("could not find package: "+pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_name+" to create robot urdf file with. Make sure you have chosen the right abb metapackage or support package. Option abb_packkage:=<abb or abb_experimental>, use option list_robots to list robots in each package")
        print_log()
        exit()

# reset pth to original support package
pth_origin_pkg_support = pth_ros_downloads+arg_abb_package+"/"+arg_robot_support_name+"/"

#copy support, moveit_config, industrial packages to project
create_directory_if_not_existing(pth_pkg_config)
create_directory_if_not_existing(pth_pkg_support)

copy_dir_to_dir(pth_origin_pkg_config, pth_project_packages)
copy_dir_to_dir(pth_origin_pkg_support, pth_project_packages)

copy_dir_to_dir(pth_ros_downloads+"abb/abb_irb2400_moveit_config/.setup_assistant", pth_pkg_config)

# get specific robot name from xacro file
specific_robot_ext = ""
for file in glob.glob(pth_pkg_support+"/urdf/"+sysarg_robot_name+"*"+"_macro.xacro"):
    specific_robot_ext = re.sub(pth_pkg_support+"/urdf/", "", file)
    specific_robot_ext = re.sub("_macro.xacro", "", specific_robot_ext)

if(specific_robot_ext == ""):
    log.append("failed to get specific robot extension. Script will exit")
    exit()

# pre editing to convert xacro to urdf format
with open(pth_pkg_support+"urdf/"+specific_robot_ext+"_macro.xacro") as f:
    subprocess.call(["rm", "-r", pth_pkg_support+"urdf/"+specific_robot_ext+".urdf.temp"])
    urdf_file = open(pth_pkg_support+"urdf/"+specific_robot_ext+".urdf.temp", "w+")
    for line in f:
        line = re.sub('<xacro:macro name="'+specific_robot_ext+'" params="prefix">', "", line)
        line = re.sub('<robot xmlns:xacro=.*?>', '<robot name="'+sysarg_robot_name+'" xmlns:xacro="http://ros.org/wiki/xacro">', line)
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
with open(pth_pkg_support+"urdf/"+specific_robot_ext+".urdf", "wb+", 0) as out:
   subprocess.call(['rosrun', 'xacro', 'xacro', pth_pkg_support+"urdf/"+specific_robot_ext+".urdf.temp"], stdout=out)
   log.append("Created urdf from xacro file")
   subprocess.call(["rm", "-r", pth_pkg_support+"urdf/"+specific_robot_ext+".urdf.temp"])

# build project
subprocess.call(["mkdir", "-p", pth_project_packages])
subprocess.call(["catkin_init_workspace"], shell=True, cwd=pth_project_packages)
subprocess.call(["catkin_make"], shell=True, cwd=pth_catkin_workspace)

# Done
print_log()
print("\n---Next steps---")
print("\n1: Succesfully run the script. This created a project: "+ sysarg_project_name +" with package: "+arg_robot_package_name+ " for the moveit configuration and package: "+arg_robot_support_name+" consisting the robot defs such as the urdf for "+sysarg_robot_name+". The urdf is ready for MoveIT! setup assistant. Do not forget to source you project before using setupassistant.")
print("\n2: use the following commands to start moveit setup assitant after sourcing your project: \n - source "+pth_catkin_workspace+"devel/setup.bash \n - roslaunch moveit_setup_assistant setup_assistant.launch")
print("\n3: When saving moveit configuration with setup assistant remember to save in package folder, path:"+pth_pkg_config)
print("\n4: Afterwards you must run simSetup.py to setup simulation and make it possible to build the project or create other configs with setup assistant")

# delete existing script config
if(os.path.exists(pth_pkg_config+"sim_setup_config.txt")):
    subprocess.call(["rm", pth_pkg_config+"sim_setup_config.txt"])

# create new custom config
with open(pth_pkg_config+"sim_setup_config.txt", "a+") as config:
    config.write("project_name="+sysarg_project_name+"\n")
    config.write("package_name="+arg_robot_package_name+"\n")
    config.write("robot_name="+sysarg_robot_name+"\n")
    config.write("abb_meta_package="+arg_abb_package+"\n")
    config.write("support_package="+arg_robot_support_name+"\n")
    config.close()