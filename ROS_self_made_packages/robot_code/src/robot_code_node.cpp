#include <ros/ros.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

int main(int argc, char* argv[])
{
    //ros ini, ros node and spinner setup
    ros::init(argc, argv, "robot_code");
    //ros::NodeHandle node;

    ros::AsyncSpinner spinner(1);
    spinner.start();

   //move group setup
    static const std::string planning_group = "group1";
    moveit::planning_interface::MoveGroupInterface move_group(planning_group);
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    const robot_state::JointModelGroup* joint_model_group = move_group.getCurrentState()->getJointModelGroup(planning_group);

    //Plan a new path using a pose/ !not executing yet
    geometry_msgs::Pose target_pose1;
    int input;
    std::cout << "orientation: \n";
    std::cin >> input;
    target_pose1.orientation.w = input;
    std::cout << "orientation: \n";
    std::cin >> input;
    target_pose1.position.x = input;
    std::cout << "orientation: \n";
    std::cin >> input;
    target_pose1.position.y = input;
    std::cout << "orientation: \n";
    std::cin >> input;
    target_pose1.position.z = input;
   
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