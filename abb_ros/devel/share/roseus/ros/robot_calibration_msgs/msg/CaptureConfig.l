;; Auto-generated. Do not edit!


(when (boundp 'robot_calibration_msgs::CaptureConfig)
  (if (not (find-package "ROBOT_CALIBRATION_MSGS"))
    (make-package "ROBOT_CALIBRATION_MSGS"))
  (shadow 'CaptureConfig (find-package "ROBOT_CALIBRATION_MSGS")))
(unless (find-package "ROBOT_CALIBRATION_MSGS::CAPTURECONFIG")
  (make-package "ROBOT_CALIBRATION_MSGS::CAPTURECONFIG"))

(in-package "ROS")
;;//! \htmlinclude CaptureConfig.msg.html
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass robot_calibration_msgs::CaptureConfig
  :super ros::object
  :slots (_joint_states _features ))

(defmethod robot_calibration_msgs::CaptureConfig
  (:init
   (&key
    ((:joint_states __joint_states) (instance sensor_msgs::JointState :init))
    ((:features __features) (let (r) (dotimes (i 0) (push "" r)) r))
    )
   (send-super :init)
   (setq _joint_states __joint_states)
   (setq _features __features)
   self)
  (:joint_states
   (&rest __joint_states)
   (if (keywordp (car __joint_states))
       (send* _joint_states __joint_states)
     (progn
       (if __joint_states (setq _joint_states (car __joint_states)))
       _joint_states)))
  (:features
   (&optional __features)
   (if __features (setq _features __features)) _features)
  (:serialization-length
   ()
   (+
    ;; sensor_msgs/JointState _joint_states
    (send _joint_states :serialization-length)
    ;; string[] _features
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _features)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; sensor_msgs/JointState _joint_states
       (send _joint_states :serialize s)
     ;; string[] _features
     (write-long (length _features) s)
     (dolist (elem _features)
       (write-long (length elem) s) (princ elem s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; sensor_msgs/JointState _joint_states
     (send _joint_states :deserialize buf ptr-) (incf ptr- (send _joint_states :serialization-length))
   ;; string[] _features
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _features (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _features i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;;
   self)
  )

(setf (get robot_calibration_msgs::CaptureConfig :md5sum-) "f347b595aa5cb3d9820e25d6d41f25cd")
(setf (get robot_calibration_msgs::CaptureConfig :datatype-) "robot_calibration_msgs/CaptureConfig")
(setf (get robot_calibration_msgs::CaptureConfig :definition-)
      "# Pose the robot should be put in for this sample
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

")



(provide :robot_calibration_msgs/CaptureConfig "f347b595aa5cb3d9820e25d6d41f25cd")


