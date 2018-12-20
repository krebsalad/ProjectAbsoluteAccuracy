/*
 * Copyright (C) 2015 Fetch Robotics Inc.
 * Copyright (C) 2013-2014 Unbounded Robotics Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Author: Michael Ferguson

#ifndef ROBOT_CALIBRATION_CAPTURE_CONST_BLINK_LED_FINDER_H
#define ROBOT_CALIBRATION_CAPTURE_CONST_BLINK_LED_FINDER_H

#include <ros/ros.h>
#include <robot_calibration/capture/depth_camera.h>
#include <robot_calibration/plugins/feature_finder.h>
#include <robot_calibration_msgs/CalibrationData.h>

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

namespace robot_calibration
{

/** @brief This class processes the point cloud input to find the LED. */
class ConstBlinkLedFinder : public FeatureFinder
{
public:
  ConstBlinkLedFinder();
  bool init(const std::string& name, ros::NodeHandle & n);
  bool find(robot_calibration_msgs::CalibrationData * msg);

private:
  bool findInternal(robot_calibration_msgs::CalibrationData * msg);

  void cameraCallback(const sensor_msgs::PointCloud2::ConstPtr& cloud);
  bool waitForCloud();
  bool getCurrentCloudAsImageMsg(sensor_msgs::Image& msg);

  //debugging function for images
  void writeCvImage(cv_bridge::CvImagePtr bridge, std::string image_path);
  
  bool getDifferenceBetweenImages(cv_bridge::CvImagePtr bridge_1, cv_bridge::CvImagePtr bridge_2, cv_bridge::CvImagePtr diff_bridge);
  bool findCenterOfPointOfInterest(cv_bridge::CvImagePtr bridge, cv::Point2f& point);

  ros::Subscriber subscriber_;  /// Incoming sensor_msgs::PointCloud2
  ros::Publisher publisher_;  /// Outgoing sensor_msgs::PointCloud2

  bool waiting_;
  sensor_msgs::PointCloud2 cloud_;
  DepthCameraInfoManager depth_camera_manager_;

  /*
   * ROS Parameters
   */
  std::string camera_sensor_name_;
  std::string chain_sensor_name_;

  cv_bridge::CvImagePtr last_cv_image;
  
};

}  // namespace robot_calibration

#endif  // ROBOT_CALIBRATION_CAPTURE_CONST_BLINK_LED_FINDER_H
