abb_ros

this is a calibration meta package for abb robots. 

Self Made packages descriptions:
- abb_irb_moveit_config: Files needed to use moveit for planning for the robot
- abb_irb_support: Files consisting definitions such as the URDF. Also meshes can be found here.  
- moveit_helper_scripts: usefull scripts to create initial project and or make changes to moveit_config
- robot_code: utility for controlling the robot using moveit c++ pipeline. Has cartesian path functionality
- abb_robot_calibration: robot_calibration custom implementation
- fieldlab_cel3_calib: Specific calibration configuration for the robot in fieldlab cel3

Dependencies description :
- abb_driver: Needed to communicate with RAPID 
- industrial_core packages: Needed for high - low end communication
- robot_calibration packages: Main calibration package. Some changes made!!
- realsense2_camera: Intel Real Sense d400 series driver
- code_coverage: dependency for robot_calibration package