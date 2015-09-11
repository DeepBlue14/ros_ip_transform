![Icon](https://github.com/DeepBlue14/image_transport_inverse/blob/master/icon.jpg)

#image_transport_inverse

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

This project is the inverse of ROS's image_transport--instead of converting non-ros --> ros, this converts ros --> non-ros.  It will use a ROS subscriber to get sensor_msgs::Image, convert it to a OpenCV Mat, and use the C socket library to send it over "vanilla" TCP/IP.


###**Dependencies**

- [ROS][3] (tested with indigo on 14.04 LTS)
- [OpenCV][4] (tested with 2.4.8)
- [Boost C++ Libraries][5]

###**Install**

**Build:**
```cd``` to the catkin directory where this package resides
and execute:
```
catkin_make
```

**Run:**
```
roslaunch openni2_launch openni2.launch
rosrun image_transport_inverse RosServer
rosrun image_transport_inverse RosClient
```


###**Future Work**

Implementation has begun for RosTopic --> TCP conversions for other data types (for example, std_msgs to std types, or to  character arrays to facilitate conversion by other languages on the client side).


[1]: http://robotics.cs.uml.edu/
[2]: http://www.uml.edu/
[3]: http://www.ros.org/
[4]: http://opencv.org/
[5]: http://www.boost.org/

