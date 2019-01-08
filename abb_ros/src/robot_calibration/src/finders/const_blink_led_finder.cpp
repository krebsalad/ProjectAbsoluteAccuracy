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

#include <sensor_msgs/PointCloud2.h>
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

namespace cpp11_patch
{
  // custom template so that c++11 patch is not needed
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
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
  // Try up to 50 frames
  for (int i = 0; i < 20; ++i)        // SET HIGHER!!!!
  {
    // temporary copy of msg, so we throw away all changes if findInternal() returns false
    robot_calibration_msgs::CalibrationData tmp_msg(*msg);
    if (findInternal(&tmp_msg))
    {
      *msg = tmp_msg;
      return true;
    }
  }
  return false;
}

bool ConstBlinkLedFinder::findInternal(robot_calibration_msgs::CalibrationData * msg)
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

  // Convert cloud to image message
  sensor_msgs::Image image_msg = sensor_msgs::Image();
  if(!(getCurrentCloudAsImageMsg(image_msg)))
  {
    return false;
  }

  // Get an OpenCV image from image_msg
  cv_bridge::CvImagePtr bridge;
  try
  {
    bridge = cv_bridge::toCvCopy(image_msg, "rgb8");  // TODO: was rgb8? does this work?
  }
  catch(cv_bridge::Exception& e)
  {
    ROS_ERROR("Conversion failed");
    return false;
  }

  //find differences
  if(!(last_cv_image))
  {
    last_cv_image = bridge;
    return false;
  }
  else if(last_cv_image->image.empty())
  {
    last_cv_image = bridge;
    return false;
  }
  else
  {    
    //create difference image
    cv_bridge::CvImagePtr diff_bridge(new cv_bridge::CvImage);
    if(!(getDifferenceBetweenImages(last_cv_image, bridge, diff_bridge)))
    {
      last_cv_image = bridge;
      return false;
    }
  
    //get point of interesent from difference image
    cv::Point2f center_point;
    if(!(findCenterOfPointOfInterest(diff_bridge, center_point)))
    {
      last_cv_image = bridge;
      return false;
    }

    //display point of interest

    //dont forget to save the current image as last image
    last_cv_image = bridge;

    // Should be TRUE when its working
    return false; 
  }

  return false;
}

void ConstBlinkLedFinder::writeCvImage(cv_bridge::CvImagePtr bridge, std::string image_path)
{
  if(!(bridge))
  {
    ROS_ERROR("display: invalid cv bridge");
    return;
  }

  //display image
  if(!(bridge->image.empty()))
  {
    cv::imwrite( image_path, bridge->image);
    ROS_WARN("displayed image at: %s", image_path.c_str());
  }
}

bool ConstBlinkLedFinder::getDifferenceBetweenImages(cv_bridge::CvImagePtr bridge_1, cv_bridge::CvImagePtr bridge_2, cv_bridge::CvImagePtr diff_bridge)
{
  // image checks
  if(bridge_1->encoding != bridge_2->encoding)
  {
    return false;
  }

  if(bridge_1->image.size != bridge_2->image.size)
  {
    ROS_WARN("bridge 1 and two have different sizes");
  }

  //create difference image
  cv::Mat diffImage;

  cv::absdiff(bridge_1->image, bridge_2->image, diffImage);

  //set difference cv bridge with difference image
  diff_bridge->header = bridge_2->header;
  diff_bridge->encoding = bridge_2->encoding;
  diff_bridge->image = diffImage;

  return true;
}

bool ConstBlinkLedFinder::getCurrentCloudAsImageMsg(sensor_msgs::Image& image_msg)
{
  if (cloud_.width == 0 && cloud_.height == 0)
  {
    return false;
  }

  sensor_msgs::PointCloud2ConstIterator<uint8_t> rgb(cloud_, "rgb");
  image_msg.encoding = "bgr8";
  image_msg.height = cloud_.height;
  image_msg.width = cloud_.width;
  image_msg.step = image_msg.width * sizeof (uint8_t) * 3;
  image_msg.data.resize(image_msg.step * image_msg.height);
  for (size_t y = 0; y < cloud_.height; y++)
  {
    for (size_t x = 0; x < cloud_.width; x++)
    {
      uint8_t* pixel = &(image_msg.data[y * image_msg.step + x * 3]);
      pixel[0] = rgb[0];
      pixel[1] = rgb[1];
      pixel[2] = rgb[2];
      ++rgb;
    }
  }

  return true;
}

bool ConstBlinkLedFinder::findCenterOfPointOfInterest(cv_bridge::CvImagePtr bridge, cv::Point2f & point)
{
  //checks
  if(bridge->image.empty())
  {
    ROS_WARN("Difference image is empty");
    return false;
  }

  //gray scaled image
  cv::Mat grayed_image;
  cv::cvtColor(bridge->image, grayed_image, CV_BGR2GRAY);

  //canny variables
  cv::Mat canny_output;
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;

  // Detect edges using canny
  cv::Canny( grayed_image, canny_output, thresh, thresh*2, 3 );

  // find contours
  cv::findContours( canny_output, contours, hierarchy, 3, 2, cv::Point(0, 0) );
  
  /// Get the moments
  std::vector<cv::Moments> mu(contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { mu[i] = cv::moments( contours[i], false ); }

  //  Get the mass centers of all countours
  std::vector<cv::Point2f> mc( contours.size() );
  for( int i = 0; i < contours.size(); i++ )
    { mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }

  //checks before trying to get single point
  if(mc.size() > 3)
  {
    ROS_ERROR("Too many differences in image, can not find blinking LED ");
    return false;
  }

  if(mc.size() < 1)
  {
    ROS_ERROR("No point was found");
    return false;
  }

  //get single the point
  float led_point_x = 0;
  float led_point_y = 0;
  float max_distance_multiple_points = 25;
  
  if(mc.size() == 2)
  {
    if(mc[0].x - mc[1].x < max_distance_multiple_points && mc[0].x - mc[1].x > -(max_distance_multiple_points))
    {
        if(mc[0].y - mc[1].y < max_distance_multiple_points && mc[0].y - mc[1].y > -(max_distance_multiple_points))
        {
            ROS_WARN("Found two points, taking average, because points close enough");
            led_point_x = (mc[0].x + mc[1].x)/2;
            led_point_y = (mc[0].y + mc[1].y)/2;
        }
        else
        {
          ROS_ERROR("Found two points, but to far apart");
          return false;
        }
    }
    else
    {
      ROS_ERROR("Found two points, but to far apart");
      return false;
    }
  }
  
  if(mc.size() == 1)
  {
    led_point_x = mc[0].x;
    led_point_y = mc[0].y;
  }

  if(led_point_x == 0 || led_point_y == 0)
  {
    ROS_ERROR("Found point @ x:0 y:0, skipping point");
    return false;
  }

  //set point
  point.x = led_point_x;
  point.y = led_point_y;
  ROS_INFO("Found point at x: %f, y: %f", point.x, point.y);

  // draw points, !!!! not required
  cv::circle(grayed_image, point, 4, cv::Scalar(0, 0, 255), 1, 8, 0);
  cv::imwrite( "/home/turtle/Desktop/LedPoints.png", grayed_image);
  ROS_WARN("displayed image resulting from findcenterofpointofinterest at: /home/turtle/Desktop/LedPoints.png \n --Press <enter> to continue--");
  std::string input;
  std::getline(std::cin, input);

  return true;
}

}  // namespace robot_calibration
