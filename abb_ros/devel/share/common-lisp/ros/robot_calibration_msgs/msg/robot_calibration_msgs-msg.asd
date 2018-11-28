
(cl:in-package :asdf)

(defsystem "robot_calibration_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :geometry_msgs-msg
               :sensor_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "CalibrationData" :depends-on ("_package_CalibrationData"))
    (:file "_package_CalibrationData" :depends-on ("_package"))
    (:file "CameraParameter" :depends-on ("_package_CameraParameter"))
    (:file "_package_CameraParameter" :depends-on ("_package"))
    (:file "CaptureConfig" :depends-on ("_package_CaptureConfig"))
    (:file "_package_CaptureConfig" :depends-on ("_package"))
    (:file "ExtendedCameraInfo" :depends-on ("_package_ExtendedCameraInfo"))
    (:file "_package_ExtendedCameraInfo" :depends-on ("_package"))
    (:file "GripperLedCommandAction" :depends-on ("_package_GripperLedCommandAction"))
    (:file "_package_GripperLedCommandAction" :depends-on ("_package"))
    (:file "GripperLedCommandActionFeedback" :depends-on ("_package_GripperLedCommandActionFeedback"))
    (:file "_package_GripperLedCommandActionFeedback" :depends-on ("_package"))
    (:file "GripperLedCommandActionGoal" :depends-on ("_package_GripperLedCommandActionGoal"))
    (:file "_package_GripperLedCommandActionGoal" :depends-on ("_package"))
    (:file "GripperLedCommandActionResult" :depends-on ("_package_GripperLedCommandActionResult"))
    (:file "_package_GripperLedCommandActionResult" :depends-on ("_package"))
    (:file "GripperLedCommandFeedback" :depends-on ("_package_GripperLedCommandFeedback"))
    (:file "_package_GripperLedCommandFeedback" :depends-on ("_package"))
    (:file "GripperLedCommandGoal" :depends-on ("_package_GripperLedCommandGoal"))
    (:file "_package_GripperLedCommandGoal" :depends-on ("_package"))
    (:file "GripperLedCommandResult" :depends-on ("_package_GripperLedCommandResult"))
    (:file "_package_GripperLedCommandResult" :depends-on ("_package"))
    (:file "Observation" :depends-on ("_package_Observation"))
    (:file "_package_Observation" :depends-on ("_package"))
  ))