#include <ros/ros.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
    //ros ini, ros node and spinner setup
    ros::init(argc, argv, "robot_code");
    ros::NodeHandle node;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    //target pose variables
    double w;
    double x;
    double y;
    double z;

    //arguments to target pose variables
    std::stringstream s_w;
    std::stringstream s_x;
    std::stringstream s_y;
    std::stringstream s_z;

    if(argv[4] != nullptr)
    {      
        s_w << argv[1];
        s_w >> w;
        
        s_x << argv[2];
        s_x >> x;

        s_y << argv[3];
        s_y >> y;

        s_z << argv[4];
        s_z >> z;
    }
    else
    {
        ROS_INFO_NAMED("irb1600", "not enough arguments given");
        return 0;
    }

   //move group setup
    static const std::string planning_group = "group1";
    moveit::planning_interface::MoveGroupInterface move_group(planning_group);
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    const robot_state::JointModelGroup* joint_model_group = move_group.getCurrentState()->getJointModelGroup(planning_group);

    //Plan a new path using a pose/ !not executing yet
    geometry_msgs::Pose target_pose1;
    int input;
    target_pose1.orientation.w = w;

    target_pose1.position.x = x;

    target_pose1.position.y = y;

    target_pose1.position.z = z;
   
    //set the target for the next path
    move_group.setPoseTarget(target_pose1);

    //create a plan and plan the path
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    bool planned = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    //execute if planning succesful
    if(planned)
    {
        ROS_INFO_NAMED("irb1600", "See RViz for planned path");
        move_group.move();
    }
    else
    {
        ROS_INFO_NAMED("irb1600", "failed planning the path");
    }
    
    return 0;
}