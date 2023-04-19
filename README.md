# ROS Robot Calibration

This is a calibration package developed for AWL during an iternship. The package is generalized for controlling abb robots with MoveIt and calibrating them with robot calibration. Note that alot of packages used here, are pulled from other repos, please heed the 'contributing' section as these packages are outdated by now. Just remember it was developed by a non professional and was only used for education/research/development purpose when i was a student. Feel free to use it as an example (though don't expect any help from me nor any changes in the future ;9).

The goal of this project is to autmatically calibrate a 6 DOF industrial robot using depth cameras.

Package descriptions brief

* abb_irbxxx_moveit_config: example moveit configuration for controlling the robot. 
    - See more: https://github.com/ros-industrial/abb
    - See more: https://github.com/ros-industrial/abb_experimental 

* abb_irbxxx_support: example of support package with the robot description such as the URDF and meshes.
    - See more: https://github.com/ros-industrial/abb
    - See more: https://github.com/ros-industrial/abb_experimental 

* moveit_helper_scripts: Usefull scripts to create initial project and or make changes to abb_irbxxx_moveit_config. The script here will download the abb repositories for generating robot packages.

* robot_code: utility for controlling the robot using moveit c++ pipeline.
    - See more: http://docs.ros.org/indigo/api/moveit_tutorials/html/doc/pr2_tutorials/planning/src/doc/move_group_interface_tutorial.html 

* abb_robot_calibration: A robot_calibration configuration. Is used to initiate calibration in combination with a specific robot calibration configuration. for example: fieldlab_cel3_calib. 

* fieldlab_cel3_calib: example of specific robot calibration configuration for the robot in fieldlab cel3. This package contains the calibration configuration which is called from abb_robot_calibration.
     - See other example at: https://github.com/fetchrobotics/fetch_ros/tree/indigo-devel
     - See toher example at: https://github.com/mikeferguson/maxwell 

Dependency description brief

* abb_driver: Needed to communicate with RAPID by inheriting from industrial_core. Also the files needed for the robot controller can be found in this package. The driver in this package differs from the official implementation. This package has joint offset support based on changes made in industrial_core and is therefore dependent on the industrial_core that can be found in this repo.
    - See more at: https://github.com/ros-industrial/abb/tree/kinetic-devel/abb_driver

* industrial_core packages: Needed for high - low end communication. Current package does have difference from original package. The main addition is an extra tranform funtion. Heed this issue regarding the changes: 
    - See more at: https://github.com/ros-industrial/industrial_core
    - Issue regarding changes: https://github.com/ros-industrial/industrial_core/issues/218

* robot_calibration packages: Main calibration package. Some changes made for logging and accepting joint states without effort. Furthermore, multiple features can be used, where not all features can be captured. Heed this issue regarding the changes: 
    - See more at: https://github.com/mikeferguson/robot_calibration 
    - Issue regarding chages: https://github.com/mikeferguson/robot_calibration/issues/65

* realsense2_camera: Intel Real Sense series driver for ros. No changes were made here.
    - See more at: https://github.com/intel-ros/realsense

* code_coverage: Dependency for robot_calibration package. No changes were made here.
    - See more at: https://github.com/mikeferguson/code_coverage 

## Getting Started

If you are new to ROS-industrial the following tutorials will help out alot.
- http://wiki.ros.org/Industrial/Tutorials

### Prerequisites

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
- git
- 

### Setting up the robot

- ROS, moveit and industrial_core are required to do the following steps. The script described in this section cover the installation aswell.

- create new catkin_project
    ```
    cd ~/
    mkdir -p ~/catkin_project/src/
    cd ~/catkin_project/src/
    catkin_init_workspace
    cd ..
    catkin_make
    source devel/setup.bash
    ```

- create the robot description
    1. You can use abb_robot_project_maker.py to generate the robot configurations
    2. Clone the git and use the helper scripts to generate robot package. Note these script require kinetic or indigo installed
    ```
    cd ~/
    mkdir -p ~/ROS_Downloads/ros-robot-calibration
    git clone git@github.com:krebsalad/ProjectAbsoluteAccuracy.git ~/ROS_Downloads/ros-robot-calibration
    python ~/ROS_Downloads/ros-robot-calibration/moveit_helper_scripts/scripts/abb_robot_project_maker.py project_name:=catkin_project robot_name:=irb1600
    ls ~/catkin_project/src/
    
    ```
    3. The above commands will generate two packages in your project. Make sure these are generated correctly with respect to the said robot.

- setup the moveit configuration for simulated and real robot
    1. The script abb_robot_project_maker.py printed steps to follow. These will also be described here
    2. To setup the moveit configuration moveit setup assistant is used. Follow the next tutorial for more about setup assistant
        - tutorial: http://docs.ros.org/kinetic/api/moveit_tutorials/html/doc/setup_assistant/setup_assistant_tutorial.html 
    3. When you are done setting up with moveit assistant, save your configuration in: ~/catkin_project/src/abb_irb1600_moveit_config/
    4. To able to launch the robot with a simulated one, an extra script was created, which can also be found in moveit_helper_scripts. This script is only useable if the package was generated with abb_robot_project_maker.py and setup assistant. On top of this, the script will add official industrial_core packages. Use the following command to run the script.
    ```
    python ~/ROS_Downloads/ros-robot-calibration/moveit_helper_scripts/scripts/abb_robot_package_sim_setup.py ~/catkin_project/src/abb_irb1600_moveit_config/
    ```

- test the robot configuration with a fake controller
    1. Run the following command after generating the packages using the script. This command will launch your robot with a fake controller.
    ```
    roslaunch abb_irb1600_moveit_config moveit_planning_execution.launch sim:=true 
    ```
    2. Move the robot using moveit plugin for Rviz
        - tutorial: http://docs.ros.org/kinetic/api/moveit_tutorials/html/doc/quickstart_in_rviz/quickstart_in_rviz_tutorial.html 

- test the robot configuration with RobotStudio simulated robot
    1. Follow the instructions in the link below to setup robotstudio
        - http://wiki.ros.org/abb/Tutorials/InstallServer
    2. After completing the above tutorial. Run the following command with ip of your simulated robot.
    ```
    roslaunch abb_irb1600_moveit_config moveit_planning_execution.launch sim:=false robot_ip:=x.x.x.x 
    ```

- test the robot configuration with an actual robot
    1. Do this after you have tried your confiuration with a simulated robot
    2. Make sure the robotsystem of the actual robot has robotware 6.05 or above
    3. Make sure the robotsystem has options multitasking and PC-interface installed
    4. There are multiple ways to install your files: 
        - connect to the controller
        - start file-transfer and move the RAPID files to your robot
        - create the options as said in the abb tutorial
    5. alternative installation:
        - connect to the controller
        - create a backup of the actual system
        - create a virtual-system using the backup
        - add your options into the virtual-system
        - test and backup your virtual system
        - use system migration to install your virtual system into the actual system. 

- utility for moving the robot
    1. A package was created to help control the robot. The package is called robot_code
    2. Move the package to your project and build
    ```
    cp -r ~/ros_downloads/ros-robot-calibration/robot_code/ ~/catkin_project/src/
    cd ~/catkin_project/
    mkdir -p src/robot_code/include
    catkin_make
    ```
    3. Use robot code node after running the robot configuration(Fake -, Simulated - or Real controller required)
    - Terminal 1 : Launch the robot
    ```
    cd ~/catkin_project/
    source devel/setup.bash
    roslaunch abb_irb1600_moveit_config moveit_planning_execution.launch sim:=true 
    ```
    - Terminal 2 : Run robot code node
    ```
    cd ~/catkin_project/
    source devel/setup.bash
    rosrun robot_code robot_code_node 
    ```
    4. Move the robot using robot code node. As an example one option from the code is going to be run.
    - Input into terminal 2, the option 'short_path_input'. It will ask for input regarding orientation and position of the end_effector. Input only the position by inputting 'n' when asked for orientation and 'y' when you want to set the value for the position (not inputting a value by typing anything other than 'y' when asked will take the current orientation and or position). Example:
    ```
    short_path_input
    n
    n
    n
    n
    y
    1.0
    y
    0.250
    y
    0.7
    ```
    5. Get the current position using robot code.
    - Input current_position to get the robot's end_effector position. (Note if no end_effector was set, the last link is used (most probably link_6))
    ```
    current_position
    ```
    6. type option exit to quit robot code, or simply close the terminal.

### setting up the cameras

- For this section, Intel RealSense cameras are required. If you want to use any other cameras or require more info about generic cameras for ROS, heed the following link:
    1. http://wiki.ros.org/Sensors/Cameras
    2. http://wiki.ros.org/camera_drivers
    3. http://wiki.ros.org/Sensors/3D%20Sensors 

- Intel RealSense SDK installation
    1. Follow the installation under installing the packages...
    https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md#installing-the-packages
    2. If any problems occur, try following the manual build.
    3. See troubleshooting for further installation problems

- Update camera firmware
    1. Follow user guide for latest firmware for d400 series
    2. https://www.intel.com/content/www/us/en/support/articles/000028171/emerging-technologies/intel-realsense-technology.html 


- Setup realsense2_camera
    1. Clone the official repository of realsense ROS driver, move to your project and build.
    ```
    git clone https://github.com/intel-ros/realsense.git ~/ROS_Downloads/realsense/
    cp -r ~/ROS_Downloads/realsense/realsense2_camera ~/catkin_project/src/
    cd ~/catkin_project/
    catkin_make
    ```
    2. Launch demo for your realsense camera
    roslaunch realsense2_camera

- Learn more about rgbd point cloud
    1. Follow the instructions here: https://github.com/intel-ros/realsense 

- (Not mandatory) Octocloud for collision detection
    1. edit abb_irbxxx_moveit_config/launch/sensor_manager.launch.xml and base it on the example given in this repository.
    2. In this file the octomap is initialised. The most important thin in this file is the octomap frame. The frame defined in the example is a camera_frame defined in the urdf. 
    3. In sensors_3d.yaml file the definitions of the topic coming from the camera can be found. Make sure to change these to the correct topic. 
        - Read more here: http://docs.ros.org/indigo/api/moveit_tutorials/html/doc/pr2_tutorials/planning/src/doc/perception_configuration.html 
    4. Note that Octomap automatically has collisions enabled. This could mess around with your planners.

- Calibrate your camera
    1. install dynamic calibrator. Can be installated for both windows and unix systems. 
        - Installation: https://www.intel.com/content/dam/support/us/en/documents/emerging-technologies/intel-realsense-technology/RealSense_D400_Dyn_Calib_User_Guide.pdf 
    2. install dynamic calibrator app or download the image and print
        - download dynamic calibrator app from googleplay for your adroid or apple-store for your iphone
        - dowload image for printing: https://www.intel.com/content/dam/support/us/en/documents/emerging-technologies/intel-realsense-technology/print-target-fixed-width.pdf
    3. run:
    ``` 
    Intel.RealSense.DynamicCalibrator
    ```
    4. follow the instruction on the dynamiccalibrator output window

### setting up the calibration

- The robot is calibrated using robot calibration package.
!!!TODO

## Built With

* ROS Kinetic kame desktop full
* moveit! desktop full
* Ubuntu 16.04 lts xenial xerus for amd64
* RealSense SDK 2.16.0
* camke version 3.5.1

## Contributing

This section covers the contribution to the official repositories. Please do check these with regards to the changes made in this repo. 

- robot calibration: https://github.com/mikeferguson/robot_calibration
- industrial core : https://github.com/ros-industrial/industrial_core
- abb experimental : https://github.com/krebsalad/abb_experimental 
- abb driver: https://github.com/krebsalad/abb 

## Versioning

- This version was created for AWL and development ended on  1 febuari.

## Authors

* **Johan Mgina** - *Initial work* - [krebsalad](https://github.com/krebsalad/ProjectAbsoluteAccuracy)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details. 
The individual packages used to create this project are licensed under there respective license.

## Acknowledgments

* Thanks to [Michael Ferguson](https://github.com/mikeferguson) for creating this awesome robot calibration package.
* Thanks to [G.A. vd. Hoorn](https://github.com/gavanderhoorn) for discussing issues regarding industrial core and abb driver
