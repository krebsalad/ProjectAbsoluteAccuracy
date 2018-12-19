cmake_minimum_required(VERSION 2.8.3)
project(fieldlab_cel3_calib)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

catkin_python_setup()

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES fieldlab_cel3_calib
#  CATKIN_DEPENDS 
#  DEPENDS system_lib
)

install(PROGRAMS
     scripts/realsense_camera_launcher.py
     DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
