/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Southwest Research Institute
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 	* Redistributions of source code must retain the above copyright
 * 	notice, this list of conditions and the following disclaimer.
 * 	* Redistributions in binary form must reproduce the above copyright
 * 	notice, this list of conditions and the following disclaimer in the
 * 	documentation and/or other materials provided with the distribution.
 * 	* Neither the name of the Southwest Research Institute, nor the names
 *	of its contributors may be used to endorse or promote products derived
 *	from this software without specific prior written permission.
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

#ifndef FLATHEADERS
#include "simple_message/messages/custom_message.h"
#include "simple_message/custom_data.h"
#include "simple_message/byte_array.h"
#include "simple_message/log_wrapper.h"
#else
#include "custom_message.h"
#include "custom_data.h"
#include "byte_array.h"
#include "log_wrapper.h"
#endif

using namespace industrial::shared_types;
using namespace industrial::byte_array;
using namespace industrial::simple_message;
using namespace industrial::custom_data;

namespace industrial
{
namespace custom_message
{

CustomMessage::CustomMessage(void)
{
  this->setMessageType(StandardMsgTypes::CUSTOM_DATA_MESSAGE);    // moet hier gedefineerd worden, message types kunnen dn ook officiel hier gedefineerd worden https://github.com/ros-industrial/industrial_core/blob/kinetic-devel/simple_message/include/simple_message/simple_message.h#L65
  this->init();
}

CustomMessage::~CustomMessage(void)
{

}

bool CustomMessage::init(industrial::simple_message::SimpleMessage & msg)
{
  bool rtn = false;
  ByteArray data = msg.getData();

  this->setMessageType(StandardMsgTypes::CUSTOM_DATA_MESSAGE);

  if (data.unload(this->data_))
  {
    if (data.unload(this->sequence_))
    {
      rtn = true;
    }
    else
    {
      rtn = false;
      LOG_ERROR("Failed to unload sequence data");
    }
  }
  else
  {
    LOG_ERROR("Failed to unload customdata data");
  }
  return rtn;
}

void CustomMessage::setSequence(shared_int sequence)
{
  this->sequence_ = sequence;
}

void CustomMessage::init(shared_int seq, CustomData& data)
{
  this->setSequence(seq);
  this->data_.copyFrom(data);
}

void CustomMessage::init()
{
  this->setSequence(0);
  this->data_.init();
}

bool CustomMessage::load(ByteArray *buffer)
{
  bool rtn = false;
  LOG_COMM("Executing customdata message load");
  if (buffer->load(this->getSequence()))
  {

    if (buffer->load(this->data_))
    {
      rtn = true;
    }
    else
    {
      rtn = false;
      LOG_ERROR("Failed to load sequence data");
    }
  }
  else
  {
    rtn = false;
    LOG_ERROR("Failed to load sequence data");
  }
  return rtn;
}

bool CustomMessage::unload(ByteArray *buffer)
{
  bool rtn = false;
  LOG_COMM("Executing customdata message unload");

  if (buffer->unload(this->data_))
  {

    if (buffer->unload(this->sequence_))
    {
      rtn = true;
    }
    else
    {
      rtn = false;
      LOG_ERROR("Failed to unload sequence data");
    }
  }
  else
  {
    rtn = false;
    LOG_ERROR("Failed to unload customdata data");
  }
  return rtn;
}

}
}