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

// get joint_offsets from description and add them to the given plan
bool computeJointOffsetsOnPlan(moveit::planning_interface::MoveGroupInterface::Plan* my_plan)
{
    std::map<std::string, float> joint_offsets;

    // get robot_Description
    std_msgs::String description_msg;
    ros::NodeHandle node;
    if(!node.getParam("/robot_description", description_msg.data))
    {
        ROS_ERROR( std::string("Failed to read /robot_description").c_str() );
        return false;
    }

    //get kdl model

    KDL::Tree model;

    if (!kdl_parser::treeFromString(std::string(description_msg.data), model))
    {
        ROS_ERROR("Failed to construct kdl tree");
        return false;
    }

    KDL::Chain chain;

    if(!model.getChain("base_link", "link_6", chain))
    {
        ROS_ERROR("Failed to construct kdl chain");
        return false;
    }

    KDL::Frame p_out = KDL::Frame::Identity();

    // for each joint
    for (unsigned int i = 0; i < chain.getNrOfSegments(); ++i)
    {
        std::string joint_name = chain.getSegment(i).getJoint().getName();

        // Apply any joint offset calibration
        if (chain.getSegment(i).getJoint().getType() != KDL::Joint::None)
        {

        }
        else
        {

        }
    }
    /// Load joint_offsets
    /*
    
 

    KDL::Tree my_tree;



    // TODO!! Get joint offsets and /joint_states and add offsets to joint offsets <--- made issue in robot_calibration git
    KDL::Chain chain;
    my_tree.getChain("link_1", "joint_6", chain);

    */
    /*for(unsigned int i = 0; i < chain.getNrOfSegments(); i++)
    {
        std::string logstr;
        KDL::Segment segment;
        segment = chain.getSegment(i);
        logstr += "Got segment: " + segment.getName();
        logstr += ", Segment has joint: " + segment.getJoint().getName();
        ROS_ERROR(logstr.c_str());
    }*/

    /*KDL::SegmentMap segment_map = my_tree.getSegments();
    for (std::map<std::string, KDL::TreeElement>::iterator it=segment_map.begin(); it!=segment_map.end(); ++it)
    {
        if(it->second)
    }*/
    
    // select only calibration tags
    // save into join_offsets per joint name the joint offsets
    
    /// get joint state messages of plan
    // create a copy of joint_angles
    //  add per joint_angle the joint_offset

    /// save copy into plan
    // exit

    /*int DOF = 6;
    for (unsigned int i = 0; i < DOF; i++)
    {
      if(model.getJoint(JointNames[i].c_str())->calibration == NULL)
        Offsets[i] = 0.0;
      else
        Offsets[i] = model.getJoint(JointNames[i].c_str())->calibration->rising.get()[0];
    }*/

}

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

int main(int argc, char* argv[])
{
    //ros ini, ros node and spinner setup
    ros::init(argc, argv, "robot_positioning_node");
    ros::NodeHandle node;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    //target pose variables
    std::stringstream pathType;

    //move group setup
    static const std::string planning_group = "group1";
    moveit::planning_interface::MoveGroupInterface move_group(planning_group);
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    // const robot_state::JointModelGroup* joint_model_group = move_group.getCurrentState()->getJointModelGroup(planning_group);


    while(ros::ok)
    {
        //ask for option
        ROS_INFO("Input utility option: options [short, cartesian, generate, current_position, exit]\n");
        std::string option_input;
        std::getline(std::cin, option_input);

        if(option_input == "short")
        {
            //create position for short path planning from given input
            ROS_INFO("please do input positions");
            custom_position* position = new custom_position();
            position->askForPositionInput();
            executeShortPath_To_Position(&move_group, position);
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

             std::vector<custom_position*> positions;
            for (int i = 0; i < num_of_positions; i++)
            {
                custom_position* position = new custom_position();
                position->askForPositionInput();
                positions.push_back(position);
            }

            executeCartesianPath_Through_Positions(&move_group, positions);

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

            std::vector<custom_position*> positions;
            for (int i = 0; i < num_of_positions; i++)
            {
                ROS_INFO(std::string("input Position "+ std::to_string(i)).c_str());
                custom_position* position = new custom_position();
                position->askForPositionInput();
                positions.push_back(position);
            }

            generatePosesFromCustomPositionToBagFile(positions, "/tmp/poses_bagfile.bag");

            for (int i = 0; i < num_of_positions; i++)
            {
                delete positions[i];
            }
        }

        if(option_input == "current_position")
        {
            //print current position off end_Effector
            ROS_WARN(std::string("Positioning info:" + getMoveGroupCurrentPositionAsString(&move_group)).c_str());
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
    }
    ROS_INFO_NAMED("positioning node:", "exited");
    return 0;
}
