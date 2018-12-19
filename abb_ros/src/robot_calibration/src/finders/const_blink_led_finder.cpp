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

#include <math.h>
#include <pluginlib/class_list_macros.h>
#include <robot_calibration/capture/const_blink_led_finder.h>
#include <robot_calibration/capture/led_finder.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <sensor_msgs/image_encodings.h>
#include <vector>


PLUGINLIB_EXPORT_CLASS(robot_calibration::ConstBlinkLedFinder, robot_calibration::FeatureFinder)

namespace robot_calibration
{
// We use a number of PC2 iterators, define the indexes here
const unsigned X = 0;
const unsigned Y = 1;
const unsigned Z = 2;

double DistancePoints(
  const geometry_msgs::Point p1,
  const geometry_msgs::Point p2)
{
  return std::sqrt((p1.x-p2.x) * (p1.x-p2.x) +
                   (p1.y-p2.y) * (p1.y-p2.y) +
                   (p1.z-p2.z) * (p1.z-p2.z));
}

ConstBlinkLedFinder::ConstBlinkLedFinder() :
  waiting_(false)
{
}

bool ConstBlinkLedFinder::init(const std::string& name,
                     ros::NodeHandle& nh)
{
  if (!FeatureFinder::init(name, nh))
    return false;

  // Setup subscriber
  std::string topic_name;
  nh.param<std::string>("topic", topic_name, "/points");
  std::string logTxt = "Constant_blinking_ledfinder subscribed to: "+topic_name;
  ROS_WARN(logTxt.c_str());

  subscriber_ = nh.subscribe(topic_name,
                             1,
                             &ConstBlinkLedFinder::cameraCallback,
                             this);

  // Name of the sensor model that will be used during optimization
  nh.param<std::string>("camera_sensor_name", camera_sensor_name_, "camera");
  nh.param<std::string>("chain_sensor_name", chain_sensor_name_, "arm");

  // Publish where led points were seen
  publisher_ = nh.advertise<sensor_msgs::PointCloud2>(getName() + "_points", 10);

  // Setup to get camera depth info
  if (!depth_camera_manager_.init(nh))
  {
    // Error will have been printed by manager
    return false;
  }

  ROS_INFO("Succefully initialized const_blink_led_finder");
  return true;
}

void ConstBlinkLedFinder::cameraCallback(const sensor_msgs::PointCloud2::ConstPtr& cloud)
{
  if (waiting_)
  {
    cloud_ = *cloud;
    waiting_ = false;
  }
}

// Returns true if we got a message, false if we timeout.
bool ConstBlinkLedFinder::waitForCloud()
{
  // Initial wait cycle so that camera is definitely up to date.
  ros::Duration(1/10.0).sleep();

  waiting_ = true;
  int count = 250;
  while (--count)
  {
    if (!waiting_)
    {
      // success
      return true;
    }
    ros::Duration(0.01).sleep();
    ros::spinOnce();
  }
  ROS_ERROR("Failed to get cloud");
  return !waiting_;
}

bool ConstBlinkLedFinder::find(robot_calibration_msgs::CalibrationData * msg)
{
  ROS_ERROR("In un implemeted led finder find function");
  // Try up to 50 frames
  std::vector<std::string> try_encoding;
  try_encoding.push_back("mono8");
  try_encoding.push_back("mono16");
  try_encoding.push_back("bgr8");
  try_encoding.push_back("rgb8");

  ROS_ERROR("here");

  for (int i = 0; i < 4; ++i)        // SET HIGHER!!!!
  {
    // temporary copy of msg, so we throw away all changes if findInternal() returns false
    robot_calibration_msgs::CalibrationData tmp_msg(*msg);
    if (findInternal(&tmp_msg, try_encoding[i]))
    {
      *msg = tmp_msg;
      return true;
    }
  }
  return false;
}

bool ConstBlinkLedFinder::findInternal(robot_calibration_msgs::CalibrationData * msg, std::string temp_enc)
{
  //cloud variables
  geometry_msgs::PointStamped rgbd;
  geometry_msgs::PointStamped world;

  // Get cloud
  if (!waitForCloud())
  {
    ROS_ERROR("No point cloud data");
    return false;
  }
  ROS_INFO("Did find point cloud data");

  // Get an image message from point cloud
  sensor_msgs::ImagePtr image_msg(new sensor_msgs::Image);
  sensor_msgs::PointCloud2ConstIterator<uint8_t> rgb(cloud_, "rgb");
  image_msg->encoding = "rgb8";
  image_msg->height = cloud_.height;
  image_msg->width = cloud_.width;
  image_msg->step = image_msg->width * sizeof (uint8_t) * 3;
  image_msg->data.resize(image_msg->step * image_msg->height);
  for (size_t y = 0; y < cloud_.height; y++)
  {
    for (size_t x = 0; x < cloud_.width; x++)
    {
      uint8_t* pixel = &(image_msg->data[y * image_msg->step + x * 3]);
      pixel[0] = rgb[0];
      pixel[1] = rgb[1];
      pixel[2] = rgb[2];
      ++rgb;
    }
  }

  // Get an OpenCV image from image_msg
  cv_bridge::CvImagePtr bridge;
  try
  {
    bridge = cv_bridge::toCvCopy(image_msg, temp_enc);  // TODO: was rgb8? does this work?
  }
  catch(cv_bridge::Exception& e)
  {
    ROS_ERROR("Conversion failed");
    return false;
  }

  //display found image
  if(!(bridge->image.empty()))
  {
    ROS_WARN("image encoding %s, image cols: %d, image rows %d", bridge->encoding.c_str(), bridge->image.cols, bridge->image.rows);
    cv::imshow( "Display window", bridge->image );
    std::string temp;
    std::getline(std::cin, temp);
  }
  else
  {
    ROS_ERROR("cv image is empty");
  }

  return false;
}

}  // namespace robot_calibration
