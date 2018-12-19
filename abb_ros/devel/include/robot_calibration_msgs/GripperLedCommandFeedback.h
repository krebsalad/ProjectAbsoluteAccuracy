// Generated by gencpp from file robot_calibration_msgs/GripperLedCommandFeedback.msg
// DO NOT EDIT!


#ifndef ROBOT_CALIBRATION_MSGS_MESSAGE_GRIPPERLEDCOMMANDFEEDBACK_H
#define ROBOT_CALIBRATION_MSGS_MESSAGE_GRIPPERLEDCOMMANDFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace robot_calibration_msgs
{
template <class ContainerAllocator>
struct GripperLedCommandFeedback_
{
  typedef GripperLedCommandFeedback_<ContainerAllocator> Type;

  GripperLedCommandFeedback_()
    {
    }
  GripperLedCommandFeedback_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct GripperLedCommandFeedback_

typedef ::robot_calibration_msgs::GripperLedCommandFeedback_<std::allocator<void> > GripperLedCommandFeedback;

typedef boost::shared_ptr< ::robot_calibration_msgs::GripperLedCommandFeedback > GripperLedCommandFeedbackPtr;
typedef boost::shared_ptr< ::robot_calibration_msgs::GripperLedCommandFeedback const> GripperLedCommandFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace robot_calibration_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'robot_calibration_msgs': ['/home/turtle/abb_ros/devel/share/robot_calibration_msgs/msg', '/home/turtle/abb_ros/src/robot_calibration_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robot_calibration_msgs/GripperLedCommandFeedback";
  }

  static const char* value(const ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
";
  }

  static const char* value(const ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GripperLedCommandFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::robot_calibration_msgs::GripperLedCommandFeedback_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // ROBOT_CALIBRATION_MSGS_MESSAGE_GRIPPERLEDCOMMANDFEEDBACK_H
