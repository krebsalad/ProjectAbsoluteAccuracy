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
    computeJointOffsetsOnPlan(&my_plan);
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
    const robot_state::JointModelGroup* joint_model_group = move_group.getCurrentState()->getJointModelGroup(planning_group);

    if(argv[1] != nullptr)
    {    
        bool none = true;
        std::stringstream path_arg;
        path_arg << argv[1];
        
        if(path_arg.str() == "short")  // shortest path plan
        {
            none = false;
            if(argv[8] != nullptr)
            {
                custom_position* position1 = new custom_position();

                position1->stream_char_to_position(argv[6], argv[7], argv[8]);
                position1->stream_char_to_orientation(argv[2], argv[3], argv[4], argv[5]);

                //plan shortest path
                executeShortPath_To_Position(&move_group, position1);
            }
            else
            {
                ROS_INFO_NAMED("positioning error:", "not enough arguments given to plan short path. w o_x o_y o_z x y z needed!");
                return 0;
            }
        }
        
        if(path_arg.str() == "cartesian")  // cartesian path plan
        {
            int numOfPos;
            if(argv[2] != nullptr)
            {
                std::stringstream nr_pos_arg;
                nr_pos_arg << argv[2];
                nr_pos_arg >> numOfPos;
            }else
            {
                ROS_INFO_NAMED("positioning error:", "to less arguments given!!");
                return 0;
            }

            none = false;

            //create custom positions from input
            if(argv[2 + (numOfPos*7)] != nullptr)
            {
                std::vector<custom_position*> positions;
                for(int i = 3; i <= 2 + (numOfPos*7); i+=7)
                {
                    custom_position* position = new custom_position();
                    position->stream_char_to_orientation(argv[i], argv[i+1], argv[i+2], argv[i+3]);
                    position->stream_char_to_position(argv[i+4], argv[i+5], argv[i+6]);
                    positions.push_back(position);
                }

                //plan cartesian path
                executeCartesianPath_Through_Positions(&move_group, positions);

                //delete routine
                for(int i = 3; i <= 2 + (numOfPos*7); i++)
                {
                    delete positions[i];
                }  
            }
            else
            {
                ROS_INFO_NAMED("positioning error:", "not enough arguments given to plan cartesian path.");
                return 0;
            }
        }

        if(path_arg.str() == "generate")  // cartesian path plan
        {
            int numOfPos;
            if(argv[2] != nullptr)
            {
                std::stringstream nr_pos_arg;
                nr_pos_arg << argv[2];
                nr_pos_arg >> numOfPos;
            }
            else
            {
                ROS_INFO_NAMED("positioning error:", "to less arguments given!!");
                return 0;
            }

            none = false;

            if(argv[2 + (numOfPos*7)] != nullptr)
            {
                std::vector<custom_position*> positions;
                for(int i = 3; i <= 2 + (numOfPos*7); i+=7)
                {
                    custom_position* position = new custom_position();
                    position->stream_char_to_orientation(argv[i], argv[i+1], argv[i+2], argv[i+3]);
                    position->stream_char_to_position(argv[i+4], argv[i+5], argv[i+6]);
                    positions.push_back(position);
                }

                //generate poses bag
                generatePosesFromCustomPositionToBagFile(positions, "/tmp/calibration_poses.bag");

                //delete routine
                for(int i = 3; i <= 2 + (numOfPos*7); i++)
                {
                    delete positions[i];
                } 
            }
            else
            {
                ROS_INFO_NAMED("positioning error:", "not enough arguments given to generate rosbag file");
                return 0;
            }
        }

	    if(path_arg.str() == "current_position")  // get current position
        {
		    ROS_WARN(std::string("Positioning info:" + getMoveGroupCurrentPositionAsString(&move_group)).c_str());
	    }

        if(none)
        {
            ROS_INFO_NAMED("positioning error:", "given path type invalid!");
        }
    }
    else
    {
        ROS_INFO_NAMED("positioning error:", "No arguments were given");
        return 0;
    }

   
    ROS_INFO_NAMED("positioning node:", "exited");
    return 0;
}
