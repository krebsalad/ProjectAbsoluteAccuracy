cmake_minimum_required(VERSION 2.8.3)
project(abb_robot_calibration)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  robot_calibration
  robot_calibration_msgs
  rospy
)

catkin_python_setup()

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES abb_robot_calibration
  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

install(PROGRAMS
     scripts/update_urdf.py
     scripts/load_joint_offsets.py
     DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)