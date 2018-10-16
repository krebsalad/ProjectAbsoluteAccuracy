cmake_minimum_required(VERSION 2.8.3)
project(webcam_calib)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED 
            cv_bridge image_transport message_generation sensor_msgs)


## Generate messages in the 'msg' folder
 add_message_files(
    FILES
    imageMsg.msg
#   Message2.msg
 )


## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   sensor_msgs  # Or other packages containing msgs
 )

catkin_package(
CATKIN_DEPENDS cv_bridge image_transport message_runtime sensor_msgs
)

find_package(OpenCV)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
 ${OpenCV_INCLUDE_DIRS}
)

# image publisher node
add_executable(image_publisher src/image_publisher.cpp)
add_dependencies(image_publisher ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(image_publisher ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

# add the subscriber example
add_executable(image_subscriber src/image_subscriber.cpp)
add_dependencies(image_subscriber ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(image_subscriber ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

# Mark executables and/or libraries for installation
install(TARGETS image_publisher image_subscriber
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
