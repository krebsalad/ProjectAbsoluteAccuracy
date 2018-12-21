# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "robot_calibration_msgs: 12 messages, 0 services")

set(MSG_I_FLAGS "-Irobot_calibration_msgs:/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg;-Irobot_calibration_msgs:/home/jmg/abb_ros/src/robot_calibration_msgs/msg;-Iactionlib_msgs:/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(robot_calibration_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg" "sensor_msgs/RegionOfInterest:std_msgs/Header:robot_calibration_msgs/ExtendedCameraInfo:sensor_msgs/CameraInfo:sensor_msgs/PointField:geometry_msgs/Point:robot_calibration_msgs/CameraParameter:sensor_msgs/Image:geometry_msgs/PointStamped:sensor_msgs/PointCloud2"
)

get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg" ""
)

get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg" "sensor_msgs/JointState:std_msgs/Header"
)

get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg" "sensor_msgs/RegionOfInterest:std_msgs/Header:robot_calibration_msgs/ExtendedCameraInfo:sensor_msgs/CameraInfo:sensor_msgs/PointField:geometry_msgs/Point:robot_calibration_msgs/CameraParameter:sensor_msgs/Image:robot_calibration_msgs/Observation:sensor_msgs/JointState:geometry_msgs/PointStamped:sensor_msgs/PointCloud2"
)

get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg" ""
)

get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg" "robot_calibration_msgs/CameraParameter:sensor_msgs/RegionOfInterest:std_msgs/Header:sensor_msgs/CameraInfo"
)

get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg" "robot_calibration_msgs/GripperLedCommandGoal:actionlib_msgs/GoalID:std_msgs/Header"
)

get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg" ""
)

get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg" "robot_calibration_msgs/GripperLedCommandFeedback:actionlib_msgs/GoalID:std_msgs/Header:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg" "robot_calibration_msgs/GripperLedCommandResult:robot_calibration_msgs/GripperLedCommandActionResult:std_msgs/Header:robot_calibration_msgs/GripperLedCommandActionGoal:robot_calibration_msgs/GripperLedCommandFeedback:robot_calibration_msgs/GripperLedCommandGoal:robot_calibration_msgs/GripperLedCommandActionFeedback:actionlib_msgs/GoalID:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg" "robot_calibration_msgs/GripperLedCommandResult:actionlib_msgs/GoalID:std_msgs/Header:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg" NAME_WE)
add_custom_target(_robot_calibration_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_calibration_msgs" "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_cpp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(robot_calibration_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(robot_calibration_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(robot_calibration_msgs_generate_messages robot_calibration_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_cpp _robot_calibration_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_calibration_msgs_gencpp)
add_dependencies(robot_calibration_msgs_gencpp robot_calibration_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_calibration_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_eus(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(robot_calibration_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(robot_calibration_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(robot_calibration_msgs_generate_messages robot_calibration_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_eus _robot_calibration_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_calibration_msgs_geneus)
add_dependencies(robot_calibration_msgs_geneus robot_calibration_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_calibration_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_lisp(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(robot_calibration_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(robot_calibration_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(robot_calibration_msgs_generate_messages robot_calibration_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_lisp _robot_calibration_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_calibration_msgs_genlisp)
add_dependencies(robot_calibration_msgs_genlisp robot_calibration_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_calibration_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_nodejs(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(robot_calibration_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(robot_calibration_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(robot_calibration_msgs_generate_messages robot_calibration_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_nodejs _robot_calibration_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_calibration_msgs_gennodejs)
add_dependencies(robot_calibration_msgs_gennodejs robot_calibration_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_calibration_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/RegionOfInterest.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/CameraInfo.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)
_generate_msg_py(robot_calibration_msgs
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg"
  "${MSG_I_FLAGS}"
  "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg;/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(robot_calibration_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(robot_calibration_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(robot_calibration_msgs_generate_messages robot_calibration_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/Observation.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CaptureConfig.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CalibrationData.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/ExtendedCameraInfo.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/src/robot_calibration_msgs/msg/CameraParameter.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionFeedback.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandAction.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandActionResult.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jmg/abb_ros/devel/share/robot_calibration_msgs/msg/GripperLedCommandGoal.msg" NAME_WE)
add_dependencies(robot_calibration_msgs_generate_messages_py _robot_calibration_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_calibration_msgs_genpy)
add_dependencies(robot_calibration_msgs_genpy robot_calibration_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_calibration_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_calibration_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(robot_calibration_msgs_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(robot_calibration_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(robot_calibration_msgs_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(robot_calibration_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_calibration_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_eus)
  add_dependencies(robot_calibration_msgs_generate_messages_eus actionlib_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(robot_calibration_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(robot_calibration_msgs_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(robot_calibration_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_calibration_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(robot_calibration_msgs_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(robot_calibration_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(robot_calibration_msgs_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(robot_calibration_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_calibration_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_nodejs)
  add_dependencies(robot_calibration_msgs_generate_messages_nodejs actionlib_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(robot_calibration_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(robot_calibration_msgs_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(robot_calibration_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_calibration_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(robot_calibration_msgs_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(robot_calibration_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(robot_calibration_msgs_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(robot_calibration_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
