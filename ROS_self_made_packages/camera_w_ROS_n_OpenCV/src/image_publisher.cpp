#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  // ROS init
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;

  //check argument 1
  if(argv[1] == NULL) 
  {
    ROS_INFO_STREAM("no argument given");
    return 1;
  }


  //image publisher setup
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);


  //video source as string
  std::istringstream video_sourceCmd(argv[1]);
  int video_source;

  //video source to int
  if(!(video_sourceCmd >> video_source))
  {
    ROS_INFO_STREAM("video source invalid. given argument could not be converted to an integer");
     return 1;
  }

  //capture video 
  cv::VideoCapture cap(video_source);

  //check if can capture
  if(!cap.isOpened()) 
  {
    ROS_INFO_STREAM("cannot capture video on cam +"+video_source);
    return 1;
  }

  //variables to convert capture to frame and ros image message
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

  //publishing rate
  ros::Rate loop_rate(5);

  //loop as long as master is on
  while (nh.ok()) {

    //capture current frame as image
    cap >> frame;
    if(!frame.empty())
    {
        //convert image to image message
        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        
        //publish
        pub.publish(msg);
        cv::waitKey(1);
    }
    else
    {
      ROS_INFO_STREAM("captured frame is empty!!");
    }

    //callback and sleep
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}

