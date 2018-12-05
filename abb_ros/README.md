abb_ros

This is a calibration package developed for AWL. The package is generalized for controlling abb_robots with MoveIt.

Self Made packages descriptions:
- abb_irbxxx_moveit_config: example moveit configuration for controlling the robot. 
- abb_irbxxx_support: example of support package. this package has files consisting definitions such as the URDF. Also meshes can be found here.

- moveit_helper_scripts: Usefull scripts to create initial project and or make changes to abb_irbxxx_moveit_config
- robot_code: utility for controlling the robot using moveit c++ pipeline. Has cartesian path functionality
- abb_robot_calibration: robot_calibration custom implementation. Is used to initiate calibration in combination with a specific robot calibration configuration. for example: fieldlab_cel3_calib
- fieldlab_cel3_calib: example of specific robot calibration configuration for the robot in fieldlab cel3

Dependencies description :
- abb_driver: Needed to communicate with RAPID by inheriting from industrial_core. Also the files needed for the robot controller can be found in this package.
- industrial_core packages: Needed for high - low end communication. Current package does have difference from original package. Such as calibration offset implementation.
- robot_calibration packages: Main calibration package. Some changes made for logging and accepting joint states without effort.
- realsense2_camera: Intel Real Sense series driver for ros. No changes were made here.
- code_coverage: Dependency for robot_calibration package. No changes were made here.

How to use...
A. Requirments
- recommended ubuntu distribution: 16.04 lts xenial xerus for amd64
    1. Download image here: 
- ros kinetic (recommended desktop full) 
    1. Installation: http://wiki.ros.org/kinetic/Installation 
- kinetic moveit (recommended desktop full)
    1. Installation: http://wiki.ros.org/kinetic/Installation/Ubuntu 
- google ceres solver: needed to run calibration
    1. Installation: http://ceres-solver.org/installation.html 
- intel realsense SDK 2.0
    1. Installation: https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md#installing-the-packages

B. Project setup
- create new catkin_project
    1. mkdir -p ~/catkin_project/src/
    2. cd ~/catkin_project/src/
    3. catkin_init_workspace
    4. cd..
    5. catkin_make
- add the robots specific configuration. (abb_irbxx_moveit_config, abb_irbxx_support)
    1. You can use moveit_helper_scripts/sripts/abb_robot_project_maker.py to generate the robot configurations
    2. Use moveit_setup_assistant to setup the moveit configuration. Save the configuration in the abb_irbxxx_moveit_config folder.
        - tutorial: http://docs.ros.org/kinetic/api/moveit_tutorials/html/doc/setup_assistant/setup_assistant_tutorial.html 
    3. You can use moveit_helper_scripts/sripts/abb_robot_package_sim_setup.py to add simulation parameters and launch files.
- for calibration and realsense camera move all folders in to src except for robot specific configuration. Do not copy abb_irbxx_moveit_config, abb_irbxx_support and fieldlab_cel3_calib unless the robot your using is the irb1660id_6_155. You can do this by cloning abb_ros package and deleting the robot specific configuration and then following the next steps.
    1. make sure ceres solver is installed
    2. cp -r ~/abb_ros/src/* ~/catkin_project/src/
    3. git clone https://github.com/mikeferguson/code_coverage ~/catkin_project/src/code_coverage
    4. cd ~/catkin_project/
    5. catkin_make clean
    6. catkin_make

C. setup the robot controller
- Using simulated robot
    1. Follow the instructions in the link below.
        - http://wiki.ros.org/abb/Tutorials/InstallServer
- Using actual robot
    1. Do this after you have tried your confiuration with a simulated robot
    2. Make sure the robotsystem of the actual robot has robotware 6.05 or above
    3. Make sure the robotsystem has options multitasking and PC-interface
    4. There are multiple ways to install your files: 
        - connect to the controller
        - start file-transfer and move the RAPID files to your robot
        - create the options as said in the tutorial
    5. alternative installation:
        - connect to the controller
        - create a backup of the current system
        - create a virtual-system using the backup
        - add your options in to the virtual-system
        - export the controller parameters from the virtual-system
        - import the controller parameters into the actual robot

D. running moveit configuration with the robot
- Move the robot with Rviz. This requires the robot to be running.
    1. running the simulated robot: http://wiki.ros.org/abb/Tutorials/RunServer 
    2. source your project. 
    3. roslaunch abb_irbxxx_moveit_config moveit_planning_exectuion sim:=false robot_ip:=192.168.178.22
- Move the robot with robot_code
    1. Before doing this, make sure you can control the robot using a simulated robot.
    2. when planning_execution is running and the simulated robot is running, start a new terminal and source the project.
    3. rosrun robot_code robot_code_node
    4. You will be asked for input
    5. input 'short'
    6. The orientaiton will be asked, afterwards the transition. (Don't know what values? Use frames in robotstudio. If your using the actual robot, first move the robot with rviz and make sure it does not collide with anything, then run robot_code_node with input 'curren_position' and note the position. Next time you can use these positions to always go the same pose)

E. Testing RealSense camera
- make sure the sdk installed properly
    1. plug in your realsense camera
    2. run: realsense-viewer
    3. Is the camera found?
- rgbd point cloud
    1. Follow the instructions here: https://github.com/intel-ros/realsense 
- octocloud for collision detection
    1. edit abb_irbxxx_moveit_config/launch/sensor_manager.launch.xml to look like abb_irb1660_moveit_config/launch/sensor_manager.launch.xml
    2. In this file the octomap is initialised. The most important in this file is the octomap frame. The frame defined in the example is a camera_frame defined in the urdf. Read further (F) for more about the frame and joints. Also the file sensors_3d.yaml is called in this launch file.
    3. In sensors_3d.yaml file the definitions of the topic coming from the camera can be found. Make sure to change these to the correct topic. 
        - Read more here: http://docs.ros.org/indigo/api/moveit_tutorials/html/doc/pr2_tutorials/planning/src/doc/perception_configuration.html 
    4. Note that Octomap is only usefull when you mount the camera for calibration, or else it will mess around with your collisions and will prevent planning new paths.

F. Calibrating the camera
- install dynamic calibrator
    1. Can be installated for windows too. 
        - Installation: https://www.intel.com/content/dam/support/us/en/documents/emerging-technologies/intel-realsense-technology/RealSense_D400_Dyn_Calib_User_Guide.pdf 
- run dynamic calibration
    1. download dynamic calibrator app from googleplay
    2. run: Intel.RealSense.DynamicCalibrator
    3. follow the instruction on the dynamiccalibrator output window

G. setup the calibration
- define camera_link in your urdf
    1. add a camera_link and a camera_optical_link. You can set some meshes if you want. They should not be in any planning_group
    2. add a camera_joint and a camera_optical_joint.
    3. camera_optical_joint has a parent frame camera_link and child camera_optical_joint
    4. External camera: camera_joint has a parent frame base_link and child camera_link. The origin shoud specify the distance from the base_link tot the camera.
    5. Mounted camera: camera_joint has a parent frame link_6(or where ever you mounted the camera) and child camera_link. 

- create specific robot calibration configuration
    1. Example: fieldlab_cel3_calib
    2. create robot_cal.launch to link to your specific robot. This should launch your robot for planning paths and executing and should also launch the camera. Base this of the example. So in this case change abb_irb1660_moveit_config to abb_irbxxx_moveit_config and likewise for the support package
    3. if mounted camera: edit calibrate_mounted.yaml and capture_mounted.yaml
    4. if external camera: edit calibrate_external.yaml and capture_external.yaml
    5. The yaml files are the main way for the calibration package to find reference frames when calibrating, which will be used for calculating the offsets and camera calibration. Readmore about the yaml files here: https://github.com/mikeferguson/robot_calibration/blob/master/README.md 

- setup calibration launch files
    1. the package that initiates the calibration is abb_robot_calibration
    2. edit capture.launch. It is recommended to change the default values to your values.
    3. edit calibrate.launch. It is recommended to change the default values to your values. No need to change the calibration_data.bag this should be inputted as an option.

H. run the calibration
- manual mode
    1. roslaunch abb_robot_calibration capture.launch output_file_ext:=xtension1
    2. add some the options specifying the robot_ip, calibration configuration and manual being true if you did not change the default values.
    3. a new x-terminal will pop-up. This terminal will output the calibration routine. Simply move the robot and press enter after its on the new pose.
    4. when your done capturing samples, type exit in the x-terminal. Your files will be saved in /tmp/calibrated_urdf_xtension1.urdf and /tmp/abb_robot_calibration/calibration_data_xtension1.yaml
    5. run calibrate.launch with option of the name of the calibration_data outputted.
    6. roslaunch abb_robot_calibration calibrate.launch calibration_data:=calibration_data_xtension1.yaml. This will edit the calibrated urdf with offsets in /tmp/

- auto mode
    1. To do this you need a poses bag file. This can be generated with a script
    2. the scripts can be found in robot_calibration/scripts/capture_poses
    3. if you downloaded the official calibration package instead of the one given in this repository or you want to use other feature finders than only a checkerboard, edit capture_poses and add self.last_state_.features = ['checkerboard_finder'] under line 66
    4. run the script, and move the robot to your poses then press enter and so forth. 
    5. exit when your done. A file can be found in the directory you executed the script from.
    6. move the calibration_poses.bag to your robot calibration specific configuration. For example fieldab_cel3_calib/config/
    7. Now you can automatically run the capture.launch with option manual:=false

- updating the urdf
    1. in abb_robot_calibration/scripts/ there is a update_urdf.py script
    2. run this scripts with the path to the calibrated_urdf and the path to your abb_irbxx_moveit_config
    3. python src/abb_robot_calibration/scripts/update_urdf.py /tmp/calibrated_urdf_xtension1.urdf src/abb_irbxxx_moveit_config

- updating the camera parameters
    TODO !!!

- joint offsets based on poses
    TODO !!!

I. Troubleshooting
- If you can setup assistant cannot find your robots meshes
    1. Make sure the paths to the meshes are correct
    2. Did you source your project before running setup assistant?
- Cannot build after moving abb_ros/src/ packages to own project
    1. When files are uploaded to git all empty folders are deleted. This means that some include folders are not there after cloning the package. Simply add the said include folders in the package directory. For example: mkdir -p src/robot_code/include/
- Execution of trajectories to slow
    1. External axis configured? see: https://github.com/ros-industrial/abb/pull/155
    2. Controller is taking too long to execute trajectory? see: https://answers.ros.org/question/196586/how-do-i-disable-execution_duration_monitoring/
- realsense dynamic calibrator
    1. cannot run calibration after pressing start calibration
        - run: Intel.DynamicCalibrator.CustomRW -g
        - this will reset your calibration options to factory gold settings
- realsense camera recognized as USB 2.0 even though its a USB 3-series port
    1. working with oracle VM?
        - oracle VM does not support 3.0 very well. Try using VMware workstation player.
    2. working with VMware workstation player
        - try the problem below
    3. have you tried updating the camera firmware?
        - https://www.intel.com/content/www/us/en/support/articles/000028171/emerging-technologies/intel-realsense-technology.html 
- USB 3.0 cable not recognized at all but USB 2.0 does
    1. working with an actual machine?
        - edit /etc/default/grub (dont forget to backup first)
        - add pci=nomsi under GRUB_CMDLINE_LINYX=""
        - sudo update-grub before restarting
- need help?
    1. pm https://github.com/krebsalad 
    2. post here for issues relating robot_calibration: https://github.com/mikeferguson/robot_calibration/issues 
    3. post here for issues relating industrial_core: https://github.com/ros-industrial/industrial_core/issues 

J. Issues
- The version of industrial_robot_client in this project has calibration offset implementation. The official version doesn't, as of 4-12-2018. Follow issue:                 1. https://github.com/ros-industrial/industrial_core/issues/218.
- The official version of abb_driver RAPID code always expects paths for external axes, if configured.
    1. https://github.com/ros-industrial/abb/pull/155 
- ROS_WARN and ROS_ERROR gives warnings when compiling. These warnings have to do with std::string logs.