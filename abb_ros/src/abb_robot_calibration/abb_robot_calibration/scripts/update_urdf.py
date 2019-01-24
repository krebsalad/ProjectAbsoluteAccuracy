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
    print("\n Update_Urdf Script Log and Error list:")
    if not log:
        print("No entries in script log found.")
    else:
        count = 0
        for entry in log:
            count += 1
            print("\n"+str(count)+") "+entry)


def print_help():
    print("\n run the script with the argument being the path to the calibrated urdf FILE and the path to moveit config package DIRECTORY.")
    print("\n remember to end the path with a / or else this scripts wont work")


if not (len(sys.argv) > 2):
    print_help()
    exit()


# read argument calibration extension and package location
arg_calibrated_urdf_file = sys.argv[1]
arg_package_directory = sys.argv[2]

# check if package directory exists
if not (os.path.exists(arg_package_directory)):
    log.append("could not find moveit config directory. Expected directory: "+arg_package_directory)
    print_log()
    exit()

# check if calibrated urdf file exists
if not (os.path.exists(arg_calibrated_urdf_file)):
    log.append("could not find calibrated urdf from give path. Given path: "+arg_calibrated_urdf_file)
    print_log()
    exit()

# check if calibrated urdf file is actually a file
if not (os.path.isfile(arg_calibrated_urdf_file)):
    log.append("calibrated urdf path is not a file. Given path: "+arg_calibrated_urdf_file)
    print_log()
    exit()

# set the variables
dir_package_config = arg_package_directory
dir_project_src = os.path.dirname(os.path.dirname(dir_package_config))+"/"
file_calibrated_urdf = arg_calibrated_urdf_file

# get project src folder from given path or else the given path is invalid
if not (os.path.exists(dir_project_src)):
    log.append("no src folder before given path. Given path invalid.")
    print_log()
    exit()

# init specific paths
dir_package_support = ""
file_original_urdf = ""
file_planning_context = ""

# find planning context
if not (os.path.exists(dir_package_config+"launch/planning_context.launch")):
    log.append("could not find planning_context in moveit config package: " +dir_package_config+"launch/")
    print_log()
    exit()

file_planning_context = dir_package_config+"launch/planning_context.launch"

# open planning context and get name of current urdf and its package
with open(file_planning_context, 'r') as f:
    for line in f:
        line = str.format(line)
        if(re.match(".*?load_robot_description"+".*?robot_description"+".*?/urdf/", line)):
            file_original_urdf = re.sub("<.*?"+"/urdf/", "", line)      # take only name of urdf
            file_original_urdf = re.sub('"/>', "", file_original_urdf)  # remove /> 
            file_original_urdf = re.sub(" ", "", file_original_urdf)        # remove spaces
            file_original_urdf = re.sub("\s+\Z","",file_original_urdf)    # remove extensive white space -> back
            
            dir_package_support = re.sub("<.*?"+'textfile="', "", line)     # remove every thing before/including textfile=
            dir_package_support = re.sub("/urdf/"+'.*?>', "", dir_package_support)  # remove every thing from /urdf to >
            dir_package_support = re.sub(r'[$]', "", dir_package_support)   # remove $
            dir_package_support = re.sub(r'[(]', "", dir_package_support)   # remove ()
            dir_package_support = re.sub(r'[)]', "", dir_package_support)
            dir_package_support = re.sub("find ", "", dir_package_support)  # remove find
            dir_package_support = re.sub(" ", "", dir_package_support)      # remove spaces
            dir_package_support = re.sub("\s+\Z","",dir_package_support)    # remove extensive white space -> back
    f.close()

# check if given package is in the same project
if not (os.path.exists(dir_project_src+dir_package_support+"/")):
    log.append("could not find support package in project source folder which should have the urdf. expected path: " + dir_project_src+dir_package_support+"/")
    print_log()
    exit()

dir_package_support = dir_project_src+dir_package_support+"/"

# check if urdf can be found as stated in planning context
if not (os.path.exists(dir_package_support+"urdf/"+file_original_urdf)):
    log.append("could not find original urdf in support package: " + dir_package_support+file_original_urdf)
    print_log()
    exit()

file_original_urdf = dir_package_support+"urdf/"+file_original_urdf
name_original_urdf_backup = os.path.basename(file_original_urdf)+".original_backup"

# check if possible to make backup of original urdf without overwriting old backups or else add a number behind the name for a maximal of 10 times
if (os.path.exists(dir_package_support+"urdf/"+name_original_urdf_backup)):
    log.append(name_original_urdf_backup + " already existing! Trying other names...")
    temp_name = ""
    check = False
    itt = 1
    while not (check):
        temp_name = name_original_urdf_backup
        temp_name += str(itt)
        if not (os.path.exists(dir_package_support+"urdf/"+temp_name)):
            check = True
        else:
            log.append(temp_name + " already existing! retrying with other name")
        if itt > 10:
            log.append("failed to set name for backup of original urdf, to many backups existing!!")
            print_log()
            exit()
    name_original_urdf_backup = temp_name

# make backup of original urdf
subprocess.call(["sudo", "cp", file_original_urdf, dir_package_support+"urdf/"+name_original_urdf_backup])
log.append("Created copy of orignal urdf and renamed to: " + name_original_urdf_backup)

# move calibrated urdf
subprocess.call(["sudo", "cp", file_calibrated_urdf, file_original_urdf])
log.append("copied calibrated urdf and replaced the original urdf, calibrated urdf can now be found in: " + file_original_urdf)

log.append("exited succesfully")
print_log()
exit()