// Auto-generated. Do not edit!

// (in-package robot_calibration_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

class CaptureConfig {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.joint_states = null;
      this.features = null;
    }
    else {
      if (initObj.hasOwnProperty('joint_states')) {
        this.joint_states = initObj.joint_states
      }
      else {
        this.joint_states = new sensor_msgs.msg.JointState();
      }
      if (initObj.hasOwnProperty('features')) {
        this.features = initObj.features
      }
      else {
        this.features = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CaptureConfig
    // Serialize message field [joint_states]
    bufferOffset = sensor_msgs.msg.JointState.serialize(obj.joint_states, buffer, bufferOffset);
    // Serialize message field [features]
    bufferOffset = _arraySerializer.string(obj.features, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CaptureConfig
    let len;
    let data = new CaptureConfig(null);
    // Deserialize message field [joint_states]
    data.joint_states = sensor_msgs.msg.JointState.deserialize(buffer, bufferOffset);
    // Deserialize message field [features]
    data.features = _arrayDeserializer.string(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += sensor_msgs.msg.JointState.getMessageSize(object.joint_states);
    object.features.forEach((val) => {
      length += 4 + val.length;
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_calibration_msgs/CaptureConfig';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f347b595aa5cb3d9820e25d6d41f25cd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Pose the robot should be put in for this sample
    sensor_msgs/JointState joint_states
    
    # Names of feature detectors to use for this sample
    string[] features
    
    ================================================================================
    MSG: sensor_msgs/JointState
    # This is a message that holds data to describe the state of a set of torque controlled joints. 
    #
    # The state of each joint (revolute or prismatic) is defined by:
    #  * the position of the joint (rad or m),
    #  * the velocity of the joint (rad/s or m/s) and 
    #  * the effort that is applied in the joint (Nm or N).
    #
    # Each joint is uniquely identified by its name
    # The header specifies the time at which the joint states were recorded. All the joint states
    # in one message have to be recorded at the same time.
    #
    # This message consists of a multiple arrays, one for each part of the joint state. 
    # The goal is to make each of the fields optional. When e.g. your joints have no
    # effort associated with them, you can leave the effort array empty. 
    #
    # All arrays in this message should have the same size, or be empty.
    # This is the only way to uniquely associate the joint name with the correct
    # states.
    
    
    Header header
    
    string[] name
    float64[] position
    float64[] velocity
    float64[] effort
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CaptureConfig(null);
    if (msg.joint_states !== undefined) {
      resolved.joint_states = sensor_msgs.msg.JointState.Resolve(msg.joint_states)
    }
    else {
      resolved.joint_states = new sensor_msgs.msg.JointState()
    }

    if (msg.features !== undefined) {
      resolved.features = msg.features;
    }
    else {
      resolved.features = []
    }

    return resolved;
    }
};

module.exports = CaptureConfig;
