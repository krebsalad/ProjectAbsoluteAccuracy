execute_process(COMMAND "/home/turtle/abb_ros/build/abb_robot_calibration/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/turtle/abb_ros/build/abb_robot_calibration/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
