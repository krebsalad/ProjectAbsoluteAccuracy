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
#include "simple_message/custom_data.h"
#include "simple_message/shared_types.h"
#include "simple_message/log_wrapper.h"
#else
#include "custom_data.h"
#include "shared_types.h"
#include "log_wrapper.h"
#endif

using namespace industrial::shared_types;

namespace industrial
{
namespace custom_data
{

CustomData::CustomData(void)
{
  this->init();
}
CustomData::~CustomData(void)
{

}

void CustomData::init()
{
  for (int i = 0; i < this->getMaxNumData(); i++)
  {
    this->setData(i, 0.0);
  }
}

bool CustomData::setData(shared_int index, shared_real value)
{
  bool rtn = false;

  if (index < this->getMaxNumData())
  {
    this->data_[index] = value;
    rtn = true;
  }
  else
  {
    LOG_ERROR("Data index: %d, is greater than size: %d", index, this->getMaxNumData());
    rtn = false;
  }
  return rtn;
}

bool CustomData::getData(shared_int index, shared_real & value) const
{
  bool rtn = false;

  if (index < this->getMaxNumData())
  {
    value = this->data_[index];
    rtn = true;
  }
  else
  {
    LOG_ERROR("Data index: %d, is greater than size: %d", index, this->getMaxNumData());
    rtn = false;
  }
  return rtn;
}

shared_real CustomData::getData(shared_int index) const
{
  shared_real rtn = 0.0;
  this->getData(index, rtn);
  return rtn;
}
  

void CustomData::copyFrom(CustomData &src)
{
  shared_real value = 0.0;

  for (int i = 0; i < this->getMaxNumData(); i++)
  {
    src.getData(i, value);
    this->setData(i, value);
  }
}

bool CustomData::operator==(CustomData &rhs)
{
  bool rtn = true;

  shared_real lhsvalue, rhsvalue;

  for (int i = 0; i < this->getMaxNumData(); i++)
  {
    this->getData(i, lhsvalue);
    rhs.getData(i, rhsvalue);
    if (lhsvalue != rhsvalue)
    {
      rtn = false;
      break;
    }
  }
  return rtn;

}

bool CustomData::load(industrial::byte_array::ByteArray *buffer)			// zie byte sizes voor custom data
{
  bool rtn = false;
  shared_real value = 0.0;

  LOG_COMM("Executing Data load");
  for (int i = 0; i < this->getMaxNumData(); i++)
  {
    this->getData(i, value);
    rtn = buffer->load(value);
    if (!rtn)
    {
      LOG_ERROR("Failed to load Data ");
      break;
    }
  }
  return rtn;
}

bool CustomData::unload(industrial::byte_array::ByteArray *buffer)
{
  bool rtn = false;
  shared_real value = 0.0;

  LOG_COMM("Executing Data position unload");
  for (int i = this->getMaxNumData() - 1; i >= 0; i--)
  {
    rtn = buffer->unload(value);
    if (!rtn)
    {
      LOG_ERROR("Failed to unload message Data: %d from data[%d]", i, buffer->getBufferSize());
      break;
    }
    this->setData(i, value);
  }
  return rtn;
}

}
}