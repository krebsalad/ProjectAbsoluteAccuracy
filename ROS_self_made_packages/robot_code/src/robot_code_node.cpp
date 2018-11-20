#include <ros/ros.h>
#include <rosbag/bag.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <moveit/trajectory_processing/iterative_time_parameterization.h>

#include <iostream>
#include <sstream>
#include <string>

struct custom_position
{
    custom_position():w(0), x(0), y(0), z(0) {}     //default constructor
    custom_position(double _w, double _x, double _y, double _z):w(_w), x(_x), y(_y), z(_z) {} //constructor with params
    void stream_char_to_position(char* c_w, char* c_x, char* c_y, char* c_z)    //set values with stringstream
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
        s_x >> x;
        s_y >> y;
        s_z >> z;
    }
    geometry_msgs::Pose getPositionAsPose()
    {
        geometry_msgs::Pose target_pose;
        target_pose.orientation.w = w;
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
        
        if(path_arg.str() == "s")  // shortest path plan
        {
            none = false;
            if(argv[5] != nullptr)
            {
                custom_position* position1 = new custom_position();

                position1->stream_char_to_position(argv[2], argv[3], argv[4], argv[5]);

                //plan shortest path
                executeShortPath_To_Position(&move_group, position1);
            }
            else
            {
                ROS_INFO_NAMED("positioning error:", "not enough arguments given to plan short path. w x y z needed!");
                return 0;
            }
        }
        
        if(path_arg.str() == "c")  // cartesian path plan
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
            if(argv[2 + (numOfPos*4)] != nullptr)
            {
                std::vector<custom_position*> positions;
                for(int i = 3; i <= 2 + (numOfPos*4); i+=4)
                {
                    custom_position* position = new custom_position();
                    position->stream_char_to_position(argv[i], argv[i+1], argv[i+2], argv[i+3]);
                    positions.push_back(position);
                }

                //plan cartesian path
                executeCartesianPath_Through_Positions(&move_group, positions);

                //delete routine
                for(int i = 3; i <= 2 + (numOfPos*4); i+=4)
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

        if(path_arg.str() == "g")  // cartesian path plan
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

            if(argv[2 + (numOfPos*4)] != nullptr)
            {
                std::vector<custom_position*> positions;
                for(int i = 3; i <= 2 + (numOfPos*4); i+=4)
                {
                    custom_position* position = new custom_position();
                    position->stream_char_to_position(argv[i], argv[i+1], argv[i+2], argv[i+3]);
                    positions.push_back(position);
                }

                //plan cartesian path
                generatePosesFromCustomPositionToBagFile(positions, "/tmp/calibration_poses.bag");

                //delete routine
                for(int i = 3; i <= 2 + (numOfPos*4); i+=4)
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



//cartesian trajectory