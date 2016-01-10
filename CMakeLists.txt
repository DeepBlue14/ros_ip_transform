cmake_minimum_required(VERSION 2.8.3)
project(ros_ip_transform)


set(Qt5_DIR "/opt/Qt/5.5/gcc_64/lib/cmake/Qt5") #Needed for ROS only; works find without it in vanilla CMake
set(CMAKE_AUTOMOC ON)
set(QT_QMAKE_EXECUTABLE "/opt/Qt/5.5/gcc_64/bin/qmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  sensor_msgs
  std_msgs
  pcl_ros
  pcl_conversions
  dynamic_reconfigure
  cv_bridge
  ecl_threads
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

find_package(Qt5 5.5.1 EXACT REQUIRED COMPONENTS Core Gui Widgets WebSockets)
#include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories({QT_LIBRARY_DIRS})
add_definitions(${QT_DEFINITIONS})


#include_directories(${QT_INCLUDE_DIRS})
#link_directories(${QT_LIBRARY_DIRS})
#add_definitions(${QT_DEFINITIONS})

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   sensor_msgs#   std_msgs
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_ip_transform
#  CATKIN_DEPENDS roscpp rospy sensor_msgs std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(ros_ip_transform
#   src/${PROJECT_NAME}/ros_ip_transform.cpp
# )
add_library(ros_ip_transform STATIC src/RosServer.cpp src/RosClient.cpp)


## Declare a cpp executable
# add_executable(iros_ip_transform_node src/ros_ip_transform_node.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(ros_ip_transform_node ros_ip_transform_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(ros_ip_transform_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ros_ip_transform ros_ip_transform_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_ros_ip_transform.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)



#add_executable(rqt_chatterbot src/Chatterbot.cpp)
#target_link_libraries(rqt_chatterbot ${catkin_LIBRARIES})

add_executable(rqt_chatterbot_001 src/chatterbots/Chatterbot_001.cpp)
target_link_libraries(rqt_chatterbot_001 ${catkin_LIBRARIES})

add_executable(rqt_chatterbot_002 src/chatterbots/Chatterbot_002.cpp)
target_link_libraries(rqt_chatterbot_002 ${catkin_LIBRARIES})

add_executable(rqt_chatterbot_003 src/chatterbots/Chatterbot_003.cpp)
target_link_libraries(rqt_chatterbot_003 ${catkin_LIBRARIES})

add_executable(rqt_chatterbot_004 src/chatterbots/Chatterbot_004.cpp)
target_link_libraries(rqt_chatterbot_004 ${catkin_LIBRARIES})



add_executable(RosClient src/RosClient_main.cpp
                         src/RosClient.cpp)
target_link_libraries(RosClient ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(RosServer src/RosServer_main.cpp
                         src/RosServer.cpp)
target_link_libraries(RosServer ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(rqt_server src/RqtServer_main.cpp
                          src/RqtServer.cpp
                          src/RqtSpinner.cpp)
target_link_libraries(rqt_server ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
qt5_use_modules(rqt_server Core WebSockets)



#Frankenscooter-project specific:
#add_executable(DataCom src/scooter_specific/DataCom_main.cpp
#                       src/scooter_specific/DataCom.cpp)
#target_link_libraries(DataCom ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})


##---------------------------------------------------------------------------------
##For Generic CMake
##cmake_minimum_required(VERSION 2.8.3)
##project(TestApp)

##set(CMAKE_AUTOMOC ON)
##set(QT_QMAKE_EXECUTABLE "/opt/Qt/5.5/gcc_64/bin/qmake") # QT 5.5.1 installed @ /opt/Qt
##set(CMAKE_INCLUDE_CURRENT_DIR ON)


##find_package(Qt5 5.5.1 EXACT REQUIRED COMPONENTS Core WebSockets)
##add_definitions(${QT_DEFINITIONS})
##include_directories({QT_LIBRARY_DIRS})
##add_definitions(${QT_DEFINITIONS})



##add_executable(main main.cpp)
##qt5_use_modules(main Core WebSockets)

##----------------------------------------------------------------------------------
##QT w/ 14.04
##
##find_package(Qt REQUIRED COMPONENTS QtCore QtGui QtWidgets)
##include(${QT_USE_FILE})
##ADD_DEFINITIONS(${QT_DEFINITIONS})

##set(CMAKE_AUTOMOC ON)


##add_executable(rqt2_image_view src/main.cpp
##                               src/Spinner.cpp
##                               src/MasterGui.cpp)
##target_link_libraries(rqt2_image_view ${catkin_LIBRARIES})
##target_link_libraries(rqt2_image_view ${QT_LIBRARIES})
##target_link_libraries(rqt2_image_view ${OpenCV_LIBRARIES})

