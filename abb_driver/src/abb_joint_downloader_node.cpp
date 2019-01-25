/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2012, Southwest Research Institute
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *      * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *      * Neither the name of the Southwest Research Institute, nor the names
 *      of its contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "abb_driver/abb_utils.h"
#include "industrial_robot_client/joint_trajectory_downloader.h"
#include "industrial_utils/param_utils.h"

using industrial_robot_client::joint_trajectory_downloader::JointTrajectoryDownloader;
using industrial::joint_traj_pt_message::JointTrajPtMessage;

namespace StandardSocketPorts = industrial::simple_socket::StandardSocketPorts;

class ABB_JointTrajectoryDownloader : public JointTrajectoryDownloader
{
  using JointTrajectoryDownloader::init;  // so base-class init() stays visible

  bool J23_coupled_;

public:
  bool init(std::string default_ip = "", int default_port = StandardSocketPorts::MOTION)
  {
    if (!JointTrajectoryDownloader::init(default_ip, default_port))  // call base-class init()
      return false;

    if (ros::param::has("J23_coupled"))
      ros::param::get("J23_coupled", this->J23_coupled_);
    else
      J23_coupled_ = false;

    return true;
  }

  bool transform(const trajectory_msgs::JointTrajectoryPoint& pt_in, trajectory_msgs::JointTrajectoryPoint* pt_out)
  {
    // correct for parallel linkage effects, if desired
    //   - use POSITIVE factor for joint->motor correction
    abb::utils::linkage_transform(pt_in, pt_out, J23_coupled_ ? +1:0 );

    return true;
  }

  //ADDED
  bool transform_before_sending(std::vector<JointTrajPtMessage>* points)
  {
        /******************joint offset tempolary implementatin************/
    if(all_joint_offsets_.size() > 0)
    {
      // loop though all points
      for(unsigned int iter = 0; iter < points->size(); iter++) 
      {
        // get joint data of point as jointData object
        industrial::joint_data::JointData j_data;
        (*points)[iter].point_.getJointPosition(j_data);

        // set joint offsets into copy of jointData
        for(industrial::shared_types::shared_int i = 0; i <  j_data.getMaxNumJoints(); i++)
        {
          // get joint value
          industrial::shared_types::shared_real value;
          if(j_data.getJoint(i, value))
          {
              // set joint value with offset
              value += all_joint_offsets_[i];
              j_data.setJoint(i, value);
          }
          else
          {
            break;
          }
        }

        //set new joint data (only the positions)
        (*points)[iter].point_.setJointPosition(j_data);
      }
    }
    else
    {
      ROS_DEBUG("Did not apply joint offsets");
    }
    /****************************************************************/
    return true;
  }

  bool calc_velocity(const trajectory_msgs::JointTrajectoryPoint& pt, double* rbt_velocity)
  {
    *rbt_velocity = 0;  // unused by ABB driver
    return true;
  }

  //ADDED
  void SetJointOffsets(const std::vector<float> &joint_offsets)
  {
  this->all_joint_offsets_ = joint_offsets;
  }

private:
  std::vector<float> all_joint_offsets_; //ADDED

};

int main(int argc, char** argv)
{
  // initialize node
  ros::init(argc, argv, "motion_interface");

  // launch the default JointTrajectoryDownloader connection/handlers
  ABB_JointTrajectoryDownloader motionInterface;
  motionInterface.init();

  /***added!!*******************************************************************/
  motionInterface.SetJointOffsets(abb::utils::getJointOffsetsFromParam(10));   
  /**************************************************************************/
  motionInterface.run();

  return 0;
}
