# Install script for directory: /home/turtle/abb_ros/src/robot_calibration_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/turtle/abb_ros/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_calibration_msgs/action" TYPE FILE FILES "/home/turtle/abb_ros/src/robot_calibration_msgs/action/GripperLedCommand.action")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_calibration_msgs/msg" TYPE FILE FILES
    "/home/turtle/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg"
    "/home/turtle/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg"
    "/home/turtle/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg"
    "/home/turtle/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg"
    "/home/turtle/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg"
    "/home/turtle/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg"
    "/home/turtle/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_calibration_msgs/msg" TYPE FILE FILES
    "/home/turtle/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg"
    "/home/turtle/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg"
    "/home/turtle/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg"
    "/home/turtle/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg"
    "/home/turtle/abb_ros/src/robot_calibration_msgs/msg/Observation.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_calibration_msgs/cmake" TYPE FILE FILES "/home/turtle/abb_ros/build/robot_calibration_msgs/catkin_generated/installspace/robot_calibration_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/turtle/abb_ros/devel/include/robot_calibration_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/turtle/abb_ros/devel/share/roseus/ros/robot_calibration_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/turtle/abb_ros/devel/share/common-lisp/ros/robot_calibration_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/turtle/abb_ros/devel/share/gennodejs/ros/robot_calibration_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/turtle/abb_ros/devel/lib/python2.7/dist-packages/robot_calibration_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/turtle/abb_ros/devel/lib/python2.7/dist-packages/robot_calibration_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/turtle/abb_ros/build/robot_calibration_msgs/catkin_generated/installspace/robot_calibration_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_calibration_msgs/cmake" TYPE FILE FILES "/home/turtle/abb_ros/build/robot_calibration_msgs/catkin_generated/installspace/robot_calibration_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_calibration_msgs/cmake" TYPE FILE FILES
    "/home/turtle/abb_ros/build/robot_calibration_msgs/catkin_generated/installspace/robot_calibration_msgsConfig.cmake"
    "/home/turtle/abb_ros/build/robot_calibration_msgs/catkin_generated/installspace/robot_calibration_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_calibration_msgs" TYPE FILE FILES "/home/turtle/abb_ros/src/robot_calibration_msgs/package.xml")
endif()

