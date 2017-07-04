cmake_minimum_required(VERSION 2.8.3)
project(theatre_bot)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  sensor_msgs
  cv_bridge
  message_generation
  ar_track_alvar
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV)

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
 add_message_files(
   FILES
	EmotionMessage.msg
	KeeponMessage.msg
	TriskarSmallUpper.msg
	Pose32.msg
	OdometryTriskar.msg
	TriskarVelocity.msg
	Twist32.msg
	Vector32.msg
	InitParamVelPos.msg
	EmotionsIntensities.msg
	MotorMessageTriskar.msg
	TriskarMessage.msg
	TriskarMessageEmotion.msg
	OdometriesTriskar.msg
	ActionExecutionMessage.msg
	PepperInfo.msg
	PepperUpper.msg
	PepperMove.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
	ActionService.srv
 )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
    DEPENDENCIES
    std_msgs
    geometry_msgs
    sensor_msgs
  )

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
#  LIBRARIES theatre_bot
  CATKIN_DEPENDS message_runtime roscpp rospy std_msgs
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
  ${PROJECT_SOURCE_DIR}/nodes_platforms/Keepon/lib/
  ${OpenCV_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(theatre_bot
#   src/${PROJECT_NAME}/theatre_bot.cpp
# )
#add_subdirectory(${PROJECT_SOURCE_DIR}/nodes_platforms/Keepon/lib/)
add_library(Keepon STATIC IMPORTED)
set_property(TARGET Keepon PROPERTY
                IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/nodes_platforms/Keepon/lib/libKeepon.Linux.a)
#link_directories(/usr/lib32 )
## Declare a cpp executable
# add_executable(action_modulation_node src/theatre_bot_node.cpp)
#this one should be documented to compile in odroid
#add_executable(keepon_node 
#${PROJECT_SOURCE_DIR}/nodes_platforms/Keepon/lib/libKeepon.Linux.a
#nodes_platforms/Keepon/NodeKeepon.cpp
#)

add_executable(landmark_global_position_node nodes/NodeLandmarkGlobalLocalization.cpp
)

add_executable(landmakr_position_node nodes/NodeLandmarkLocalization.cpp
src/json/jsoncpp.cpp
src/WorldModelDescription/TheatrePlaces.cpp
src/WorldModelDescription/MarkerPosition.cpp
src/Parameters/ConfigurationParameters/ReactiveModelParameters.cpp
src/Parameters/ConfigurationParameters/AnalyzerParameters.cpp
src/Parsers/ParserConfigurationFiles.cpp
src/Parsers/KalmanParser.cpp)

add_executable(not_do_anything_execution_node nodes/NodeNotDoAnythingActionExecution.cpp
src/json/jsoncpp.cpp
)

add_executable( body_action_node nodes nodes/NodeBodyActionExecution.cpp
src/json/jsoncpp.cpp
src/Parsers/EmotionParser.cpp
src/Parameters/Parameter.cpp
src/Parameters/MovementParameters/Quaternion.cpp
src/Parameters/MovementParameters/Position.cpp
src/Parameters/EmotionalParameters/EmotionParameter.cpp
src/Parameters/EmotionalParameters/EmotionMovementParameter.cpp
src/Parameters/MovementParameters/Position.cpp
src/Parameters/MovementParameters/Square.cpp
src/Parameters/MovementParameters/Point.cpp
src/Parameters/MovementParameters/Amplitude.cpp
src/Parameters/MovementParameters/Circle.cpp
src/Parameters/MovementParameters/Landmark.cpp
src/PlatformActionControllers/Body/BodyAction.cpp
src/PlatformActionControllers/Body/TriskarSmallBody.cpp
src/PlatformActionControllers/Body/TriskarPlanner.cpp
src/PlatformActionControllers/Body/KeeponBody.cpp
src/PlatformActionControllers/Body/PepperBody.cpp
src/WorldModelDescription/TheatrePlaces.cpp
src/WorldModelDescription/MarkerPosition.cpp
src/Parsers/ParserConfigurationFiles.cpp
src/Parameters/ConfigurationParameters/ReactiveModelParameters.cpp
src/Parameters/ConfigurationParameters/AnalyzerParameters.cpp
)

add_executable(shoulder_action_node nodes/NodeShoulderActionExecution.cpp
src/json/jsoncpp.cpp
src/Parsers/EmotionParser.cpp
src/Parameters/Parameter.cpp
src/Parameters/MovementParameters/Quaternion.cpp
src/Parameters/MovementParameters/Position.cpp
src/Parameters/EmotionalParameters/EmotionParameter.cpp
src/Parameters/EmotionalParameters/EmotionMovementParameter.cpp
src/Parameters/MovementParameters/Amplitude.cpp
src/PlatformActionControllers/Shoulder/TriskarSmallShoulder.cpp
src/PlatformActionControllers/Shoulder/PepperShoulder.cpp
src/PlatformActionControllers/Shoulder/ShoulderAction.cpp
)

add_executable(torso_action_node nodes/NodeTorsoActionExecution.cpp
src/json/jsoncpp.cpp
src/Parsers/EmotionParser.cpp
src/Parameters/Parameter.cpp
src/Parameters/MovementParameters/Quaternion.cpp
src/Parameters/MovementParameters/Position.cpp
src/Parameters/EmotionalParameters/EmotionParameter.cpp
src/Parameters/EmotionalParameters/EmotionMovementParameter.cpp
src/Parameters/MovementParameters/Amplitude.cpp
src/PlatformActionControllers/Torso/KeeponTorso.cpp
src/PlatformActionControllers/Torso/TriskarSmallTorso.cpp
src/PlatformActionControllers/Torso/PepperTorso.cpp
src/PlatformActionControllers/Torso/TorsoAction.cpp
)

add_executable(action_modulation_node nodes/NodeActionModulation.cpp
src/json/jsoncpp.cpp
src/ActionModulation/ActionExecution.cpp
src/ActionModulation/ActionModulation.cpp
src/ActionModulation/ActionModulationSubSystem.cpp
src/ActionModulation/ActionAddition.cpp
src/Parsers/ParserAction.cpp
src/ActionDescription/SimpleActions/SimpleActionMoveShoulder.cpp
src/ActionDescription/SimpleActions/SimpleActionOscillateBody.cpp
src/ActionDescription/SimpleActions/SimpleActionMoveTorso.cpp
src/ActionDescription/SimpleActions/SimpleActionDoNothing.cpp
src/ActionDescription/SimpleActions/SimpleActionSpeak.cpp
src/ActionDescription/SimpleActions/SimpleActionOscillateTorso.cpp
src/ActionDescription/SimpleActions/SimpleActionOscillateShoulder.cpp
src/ActionDescription/SimpleActions/SimpleActionMoveBody.cpp
src/ActionDescription/AbstractActionDescription.cpp
src/ActionDescription/CompositeActionDescription.cpp
src/ActionDescription/SimpleActionDescription.cpp
src/ActionDescription/CompositeActions/CompositeActionWalk.cpp
src/EmotionDescription/ActionChanges.cpp
src/EmotionDescription/EmotionProfile.cpp
src/LoadInformation/Load.cpp
src/LoadInformation/CharacterPaceLoad.cpp
src/LoadInformation/PlatformLoad.cpp
src/LoadInformation/EmotionalLoad.cpp
src/ContextDescription/AbstractContextDescription.cpp
src/ContextDescription/SimpleContextDescription.cpp
src/ContextDescription/CompositeContextDescription.cpp
src/Parameters/SpeakParameters/Speak.cpp
src/Parameters/MovementParameters/Quaternion.cpp
src/Parameters/MovementParameters/Position.cpp
src/Parameters/MovementParameters/Square.cpp
src/Parameters/MovementParameters/Point.cpp
src/Parameters/MovementParameters/Amplitude.cpp
src/Parameters/MovementParameters/Circle.cpp
src/Parameters/MovementParameters/Landmark.cpp
src/Parameters/Parameter.cpp
src/Parameters/TimeParameters/Velocity.cpp
src/Parameters/TimeParameters/Time.cpp
src/Parameters/CharacterParameters/CharacterMovementModification.cpp
src/Parameters/CharacterParameters/CharacterEmotionModification.cpp
src/Parameters/EmotionalParameters/EmotionMovementParameter.cpp
src/Parameters/EmotionalParameters/EmotionParameter.cpp
)

add_executable(emotion_model_node nodes/NodeEmotionalModel.cpp
src/json/jsoncpp.cpp
src/WorldModelDescription/TheatrePlaces.cpp
src/WorldModelDescription/MarkerPosition.cpp
src/Parsers/ParserConfigurationFiles.cpp
src/Parameters/ConfigurationParameters/ReactiveModelParameters.cpp
src/Parameters/ConfigurationParameters/AnalyzerParameters.cpp
src/EmotionalModel/EmotionalModel.cpp
src/EmotionalModel/ReactiveModel.cpp
src/EmotionalModel/EventAnalyzer.cpp
src/EmotionalModel/EmotionEventAnalyzer/EventFearAnalyzer.cpp
src/EmotionalModel/EmotionEventAnalyzer/EventInterestAnalyzer.cpp
src/EmotionalModel/EmotionEventAnalyzer/EventReliefAnalyzer.cpp
src/EmotionalModel/EmotionEventAnalyzer/EventSurpriseAnalyzer.cpp
)

target_link_libraries(emotion_model_node ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}) 
target_link_libraries(body_action_node ${catkin_LIBRARIES}) 
target_link_libraries(action_modulation_node ${catkin_LIBRARIES}) 
target_link_libraries(torso_action_node ${catkin_LIBRARIES})
target_link_libraries(shoulder_action_node ${catkin_LIBRARIES})
target_link_libraries(not_do_anything_execution_node ${catkin_LIBRARIES}) 
target_link_libraries(landmakr_position_node ${catkin_LIBRARIES})
target_link_libraries(landmark_global_position_node ${catkin_LIBRARIES})

#this one should be documented to compile in odroid
#set_target_properties(keepon_node PROPERTIES COMPILE_FLAGS "-DHARDWARE=3" LINK_FLAGS "-DHARDWARE=3")
#target_link_libraries(keepon_node Keepon ${catkin_LIBRARIES} 
#) 

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(theatre_bot_node theatre_bot_generate_messages_cpp)
add_dependencies(action_modulation_node theatre_bot_generate_messages_cpp)
add_dependencies(emotion_model_node theatre_bot_generate_messages_cpp)
add_dependencies(body_action_node theatre_bot_generate_messages_cpp)
add_dependencies(torso_action_node theatre_bot_generate_messages_cpp)
add_dependencies(not_do_anything_execution_node theatre_bot_generate_messages_cpp)
add_dependencies(shoulder_action_node theatre_bot_generate_messages_cpp)
add_dependencies(landmakr_position_node theatre_bot_generate_messages_cpp)
add_dependencies(landmark_global_position_node theatre_bot_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(theatre_bot_node
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
# install(TARGETS theatre_bot theatre_bot_node
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
# catkin_add_gtest(${PROJECT_NAME}-test test/test_theatre_bot.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
