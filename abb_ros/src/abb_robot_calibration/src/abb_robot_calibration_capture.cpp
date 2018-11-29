#include <ros/ros.h>
#include <robot_calibration/capture/chain_manager.h>


int main(int argc, char* argv[])
{
    //ros ini, ros node and spinner setup
    ros::init(argc, argv, "abb_robot_calibration_capture");
    ros::NodeHandle node("abb_rc_capture");

    //initialize chain manager
    //robot_calibration::ChainManager* chainManager = new robot_calibration::ChainManager(node, 0.15);


}