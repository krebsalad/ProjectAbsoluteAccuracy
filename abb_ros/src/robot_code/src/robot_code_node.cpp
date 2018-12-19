#include <ros/ros.h>
#include <rosbag/bag.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <moveit/trajectory_processing/iterative_time_parameterization.h>
#include <std_msgs/String.h>

#include <iostream>
#include <sstream>    
#include <string>
#include <map>

#include <kdl_parser/kdl_parser.hpp>
#include <visualization_msgs/Marker.h>


namespace robot_positioning_utility
{

struct custom_position
{
    custom_position():w(0), x(0), y(0), z(0), o_x(0), o_y(0), o_z(0) {}     //default constructor
    custom_position(double _x, double _y, double _z):w(0), x(_x), y(_y), z(_z), o_x(0), o_y(0), o_z(0) {} //constructor with params
    void stream_char_to_position(char* c_x, char* c_y, char* c_z)    //set values with stringstream
    {
        std::stringstream s_x;
        std::stringstream s_y;
        std::stringstream s_z;
        s_x << c_x;
        s_y << c_y;
        s_z << c_z;
        
        s_x >> x;
        s_y >> y;
        s_z >> z;
    }
    void stream_char_to_orientation(char* c_w, char* c_x, char* c_y, char* c_z)    //set values with stringstream
    {
        std::stringstream s_w;
        std::stringstream s_x;
        std::stringstream s_y;
        std::stringstream s_z;
        s_w << c_w;
        s_x << c_x;
        s_y << c_y;
        s_z << c_z;
        
        s_w >> w;
        s_x >> o_x;
        s_y >> o_y;
        s_z >> o_z;
    }

    geometry_msgs::Pose getPositionAsPose()
    {
        geometry_msgs::Pose target_pose;
        target_pose.orientation.w = w;
        target_pose.orientation.x = o_x;
        target_pose.orientation.y = o_y;
        target_pose.orientation.z = o_z;
        target_pose.position.x = x;
        target_pose.position.y = y;
        target_pose.position.z = z;
        return target_pose;
    }
    std::string getPositionAsString()
    {
        std::string str = "[w: ";
        str += std::to_string(w) + ", x:";
        str += std::to_string(x) + ", y:";
        str += std::to_string(y) + ", z:";
        str += std::to_string(z) + "]";
        return str;
    }
    void askForPositionInput()
    {
        std::string input;
        std::stringstream stream_input[7];
        
        ROS_INFO("w:");
        std::getline(std::cin, input);
        stream_input[0].str(input);
        input = std::string();

        ROS_INFO("orientaiton_x:");
        std::getline(std::cin, input);
        stream_input[1].str(input);
        input = std::string();

        ROS_INFO("orientaiton_y:");
        std::getline(std::cin, input);
        stream_input[2].str(input);
        input = std::string();

        ROS_INFO("orientaiton_z:");
        std::getline(std::cin, input);
        stream_input[3].str(input);
        input = std::string();

        ROS_INFO("x:");
        std::getline(std::cin, input);
        stream_input[4].str(input);
        input = std::string();

        ROS_INFO("y:");
        std::getline(std::cin, input);
        stream_input[5].str(input);
        input = std::string();

        ROS_INFO("z:");
        std::getline(std::cin, input);
        stream_input[6].str(input);
        input = std::string();

        stream_input[0] >> w;
        stream_input[1] >> o_x;
        stream_input[2] >> o_y;
        stream_input[3] >> o_z;
        stream_input[4] >> x;
        stream_input[5] >> y;
        stream_input[6] >> z;
    }

    double w;
    double o_x;
    double o_y;
    double o_z;
    double x;
    double y;
    double z;
};



//shortest path trajectory
void executeShortPath_To_Position(moveit::planning_interface::MoveGroupInterface* move_group, custom_position* pos1)
{ 
    std::string txt = "planning shortpath to position" + pos1->getPositionAsString();
    ROS_INFO_NAMED("positioning execution:", txt.c_str());
    //planning path, if not changed = will stay on the same pos
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;

    //set the target for the next path
    move_group->setPoseTarget(pos1->getPositionAsPose());
    bool planned = (move_group->plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    
    //execute if planning succesful
    if(planned)
    {
        ROS_INFO_NAMED("positioning execution success:", "See RViz for planned path");
        move_group->move();
    }
    else
    {
        ROS_INFO_NAMED("positioning execution error:", "failed planning the path");
    }
}

void executeCartesianPath_Through_Positions(moveit::planning_interface::MoveGroupInterface* move_group, std::vector<custom_position*> positions)
{
    std::string allPosStr = "";
    //planning path, if not changed = will stay on the same pos
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;

    //create waypoints of the path to plan
    std::vector<geometry_msgs::Pose> poses;
    for(std::vector<custom_position*>::iterator it = positions.begin(); it != positions.end(); ++it)
    {
        poses.push_back((*it)->getPositionAsPose());
        allPosStr+=(*it)->getPositionAsString()+", ";
        ROS_INFO_NAMED("positioning:", "added waypoint");
    }

    std::string txt = "planning cartesian path through positions" + allPosStr;
    ROS_INFO_NAMED("positioning execution:", txt.c_str());

    //create trajectory message and compute path
    moveit_msgs::RobotTrajectory trajectory_msg;
    move_group->setPlanningTime(10.0);
    double frac = move_group->computeCartesianPath(poses, 0.01, 0.0, trajectory_msg, false);

    //robot trajectory object from trajectory
    robot_trajectory::RobotTrajectory r_trajectory(move_group->getCurrentState()->getRobotModel(), move_group->getName());
    r_trajectory.setRobotTrajectoryMsg(*(move_group->getCurrentState()), trajectory_msg);
    trajectory_processing::IterativeParabolicTimeParameterization It_Pa_Ti_Pa;
    bool success = It_Pa_Ti_Pa.computeTimeStamps(r_trajectory);

    r_trajectory.getRobotTrajectoryMsg(trajectory_msg);

    my_plan.trajectory_ = trajectory_msg;
    
    
    sleep(5.0);

    //execute if planning succesful
    if(success)
    {
        ROS_INFO_NAMED("positioning execution success:", "See RViz for planned path");
        move_group->execute(my_plan);
    }
    else
    {
        ROS_INFO_NAMED("positioning execution error:", "failed planning the path");
    }
}

void generatePosesFromCustomPositionToBagFile(std::vector<custom_position*> positions, std::string bagFilePath)
{
    rosbag::Bag bag;
    //create waypoints of the path to plan
    bag.open(bagFilePath, rosbag::bagmode::Write);

    for(std::vector<custom_position*>::iterator it = positions.begin(); it != positions.end(); ++it)
    {
        bag.write("pose", ros::Time::now(), (*it)->getPositionAsPose());
    }

    bag.close();


}

std::string getMoveGroupCurrentPositionAsString(moveit::planning_interface::MoveGroupInterface* move_group)
{
	geometry_msgs::Pose current_pose = move_group->getCurrentPose().pose;
	std::string strorientation = "orientation:[" ;
    std::string strPosition = "Position:[" ;
	strorientation += std::to_string(current_pose.orientation.w) + ", " + std::to_string(current_pose.orientation.x) + ", " + std::to_string(current_pose.orientation.y) + ", " + std::to_string(current_pose.orientation.z) + "], " ;
	strPosition += std::to_string(current_pose.position.x) + ", " + std::to_string(current_pose.position.y) + ", " + std::to_string(current_pose.position.z) + "]" ;
    return strorientation + strPosition;
}

visualization_msgs::Marker createVizualizationMarker(custom_position* pos, std::string namespace_name, int identifier)
{
    //create and modify frame
    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time::now();
    marker.ns = namespace_name;
    marker.id = identifier;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;

    //transform frame
    marker.pose.position.x = pos->x;
    marker.pose.position.y = pos->y;
    marker.pose.position.z = pos->z;

    //rotate frame
    marker.pose.orientation.x = pos->o_x;
    marker.pose.orientation.y = pos->o_y;
    marker.pose.orientation.z = pos->o_z;
    marker.pose.orientation.w = pos->w;

    //scale frame
    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;

    //color frame
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    //lifetime, will not be auto deleted
    marker.lifetime = ros::Duration();

    return marker;
}

}

int main(int argc, char* argv[])
{
    //ros ini, ros node and spinner setup
    ros::init(argc, argv, "robot_positioning_node");
    ros::NodeHandle node;
    ros::Rate r(1);

    ros::AsyncSpinner spinner(1);
    spinner.start();

    //target pose variables
    std::stringstream pathType;

    //move group setup
    static const std::string planning_group = "group1";
    moveit::planning_interface::MoveGroupInterface move_group(planning_group);
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    // const robot_state::JointModelGroup* joint_model_group = move_group.getCurrentState()->getJointModelGroup(planning_group);

    //setup vizualisation
    ros::Publisher viz_pub = node.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    while(ros::ok)
    {
        std::vector<visualization_msgs::Marker> pub_markers;
        //ask for option
        ROS_INFO("Input utility option: options [short, cartesian, generate, current_position, viz_point, exit]\n");
        std::string option_input;
        std::getline(std::cin, option_input);

        if(option_input == "short")
        {
            //create position for short path planning from given input
            ROS_INFO("please do input position");
            robot_positioning_utility::custom_position* position = new robot_positioning_utility::custom_position();
            position->askForPositionInput();
            robot_positioning_utility::executeShortPath_To_Position(&move_group, position);
            delete position;
        }

        if(option_input == "viz_point")
        {
            ROS_WARN("make sure rviz has a marker display and that this display is subscribed to topic /visualization_marker");
               
            //ask for extra inputs
            ROS_INFO("First, do input namespace of the frame and identifier. Note that using the same ns and identifier will result in modifying instead of creating a new one");
            std::string namespace_input;
            std::string frame_id_str;
            ROS_INFO("frame namespace:");
            std::getline(std::cin, namespace_input);
            ROS_INFO("identifier:");
            std::getline(std::cin, frame_id_str);

            //convert string to int
            int frame_id = 0;
            std::stringstream stream_input;
            stream_input.str(frame_id_str);
            stream_input >> frame_id;

            //create position
            ROS_INFO("please do input position");
            robot_positioning_utility::custom_position* position = new robot_positioning_utility::custom_position();
            position->askForPositionInput();

            //vizualize point in rviz  
            visualization_msgs::Marker marker = robot_positioning_utility::createVizualizationMarker(position, namespace_input, frame_id);
            pub_markers.push_back(marker);
            delete position;
        }

        if(option_input == "cartesian")
        {
            //create positions for cartesian path planning from given inputs
            int num_of_positions = 0;
            std::string str_n_o_p;
            ROS_INFO("how many positions?");
            std::getline(std::cin, str_n_o_p);
            num_of_positions = std::stoi(str_n_o_p);

             std::vector<robot_positioning_utility::custom_position*> positions;
            for (int i = 0; i < num_of_positions; i++)
            {
                robot_positioning_utility::custom_position* position = new robot_positioning_utility::custom_position();
                position->askForPositionInput();
                positions.push_back(position);
            }

            robot_positioning_utility::executeCartesianPath_Through_Positions(&move_group, positions);

            for (int i = 0; i < num_of_positions; i++)
            {
                delete positions[i];
            }
        }

        if(option_input == "generate")
        {
            //create positions for pose generating from given inputs
            int num_of_positions = 0;
            std::string str_n_o_p;
            ROS_INFO("how many positions?");
            std::getline(std::cin, str_n_o_p);
            num_of_positions = std::stoi(str_n_o_p);

            std::vector<robot_positioning_utility::custom_position*> positions;
            for (int i = 0; i < num_of_positions; i++)
            {
                ROS_INFO(std::string("input Position "+ std::to_string(i)).c_str());
                robot_positioning_utility::custom_position* position = new robot_positioning_utility::custom_position();
                position->askForPositionInput();
                positions.push_back(position);
            }

            // note that this is not usable for robot_calibration auto routine
            robot_positioning_utility::generatePosesFromCustomPositionToBagFile(positions, "/tmp/poses_bagfile.bag");

            for (int i = 0; i < num_of_positions; i++)
            {
                delete positions[i];
            }
        }

        if(option_input == "current_position")
        {
            //print current position off end_Effector
            ROS_WARN(std::string("Positioning info:" + robot_positioning_utility::getMoveGroupCurrentPositionAsString(&move_group)).c_str());
        }

        if(option_input == "")
        {
            ROS_INFO_NAMED("positioning error:", "given option type invalid!");
        }

        if(option_input == "exit")
        {
            ROS_INFO_NAMED("positioning node:", "exiting...");
            break;
        }

        for (int i = 0; i < pub_markers.size(); i++)
        {
            viz_pub.publish(pub_markers[i]);
        }
        
    }
    ROS_INFO_NAMED("positioning node:", "exited");
    return 0;
}
