![Icon](https://github.com/DeepBlue14/ros_ip_transform/blob/master/icon.jpg)

#image_ip_transform

*Author/Maintainer:* James Kuczynski,  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Undergraduate Researcher,  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Robotics Laboratory][1],  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[University of Massachusetts Lowell][2].  
*Email:* jkuczyns@cs.uml.edu

=====

###**Index**

- [Project Synopsis](#project-synopsis)
- [Dependencies](#dependencies)
- [Install](#install)
- [Future Work](#future-work)


###**Project Synopsis**

This project provides a framework for transformations between ROS topics and TCP/IP streams.  Using this API, the user can create a simple subscriber and/or publisher to run on the ROS system.  The syntax is almost identical to those provided by ROS, but these will implicitly carry out the specified transform.


###**Dependencies**

- [ROS][3] (tested with indigo on 14.04 LTS)
- [OpenCV][4] (tested with 2.4.8)
- [Boost C++ Libraries][5]
- [QT][6] >= 5.3 *(Only required for websocket classes)*


###**Install**

If you wish to use the websocket modules, install [QT][6] >= 5.3 using the installer script.
Install it at ```/opt/Qt```, which is QT's default installaction location.


**Build:**
```cd``` to the catkin directory where this package resides
and execute:
```
catkin_make
```
This will build the two example programs (a client and a server), as well as
generate a static library.  Of course, the source files can be copied into a
separate project location and linked and/or modified.


**Run (standard TCP):**
```
roslaunch openni2_launch openni2.launch
rosrun ros_ip_transform RosServer
rosrun ros_ip_transform RosClient
```

**Run (websockets)**
```
roscore &
rosrun ros_ip_transform rqt_server
rosrun ros_ip_transform rqt_chatterbot

rostopic echo /chatter
rostopic echo /user/chatter
```
Then start one or more clients by running the chatclient.html file located in the src folder.

###**Future Work**

Implementation has begun for RosTopic --> TCP conversions for other data types (for example, std_msgs to std types, or to character arrays to facilitate conversion by other languages on the client side).  In addition, modifications will be made so that the server does not block even if a client is not requesting.


[1]: http://robotics.cs.uml.edu/
[2]: http://www.uml.edu/
[3]: http://www.ros.org/
[4]: http://opencv.org/
[5]: http://www.boost.org/
[6]: http://www.qt.io/
