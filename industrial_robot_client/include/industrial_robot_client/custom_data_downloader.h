/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Southwest Research Institute
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *       * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *       * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *       * Neither the name of the Southwest Research Institute, nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
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

#ifndef CUSTOM_DATA_DOWNLOADER_H_
#define CUSTOM_DATA_DOWNLOADER_H_

#include <map>
#include <vector>
#include <string>

#include "ros/ros.h"
#include "industrial_msgs/CmdJointTrajectory.h"
#include "industrial_msgs/StopMotion.h"
#include "sensor_msgs/JointState.h"
#include "simple_message/smpl_msg_connection.h"
#include "simple_message/socket/tcp_client.h"
#include "simple_message/messages/custom_data_message.h"

//#include "industrial_robot_client/joint_trajectory_interface.h"

namespace industrial_robot_client
{
namespace custom_data_downloader
{

//using industrial_robot_client::joint_trajectory_interface::JointTrajectoryInterface;
using industrial::custom_data::custom_data;
using industrial::smpl_msg_connection::SmplMsgConnection;
using industrial::tcp_client::TcpClient;
namespace StandardSocketPorts = industrial::simple_socket::StandardSocketPorts;

class CustomDataDownloader //: public JointTrajectoryInterface
{

  CustomDataDownloader() //: default_joint_pos_(0.0), default_vel_ratio_(0.1), default_duration_(10.0) {};

  
  virtual bool init(std::string default_ip = "", int default_port = StandardSocketPorts::MOTION);

  virtual bool init(SmplMsgConnection* connection);

  virtual ~CustomDataDownloader();

  virtual void run() { ros::spin(); }

protected:

  //virtual void trajectoryStop();

  virtual bool string_to_msgs(const userInputMessage &msg, std::vector<CustomDataMessage>* msgs);

  virtual bool send_to_robot(const std::vector<CustomDataMessage>& messages)=0;

  virtual void userInputCB(const userInputMessage &msg);

  virtual bool is_valid(const userInputMessage &msg);

  TcpClient default_tcp_connection_;

  ros::NodeHandle node_;
  SmplMsgConnection* connection_;
  ros::Subscriber sub_user_input_;  // handle user input topic subscription
  ros::Subscriber sub_custom_data_; // handle for joint-trajectory topic subscription


  bool send_to_robot(const std::vector<CustomDataMessage>& messages);

private:
  static CustomDataMessage create_message(std::string data);

  

};

} //custom_data_downloader
} //industrial_robot_client

#endif /* CUSTOM_DATA_DOWNLOADER_H_ */
