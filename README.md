#image_transport_inverse

###**Index**

- Project Synopsis
- Dependencies
- Build & Run


###**Project Synopsis**

This project is the inverse of ROS's image_transport--instead of converting non-ros --> ros, this converts ros --> non-ros.  It will use a ROS subscriber to get sensor_msgs::Image, convert it to a OpenCV Mat, and use the C socket library to send it over "vanilla" TCP/IP.


###**Dependencies**

- C/C++
- ROS (tested with indigo on 14.04 LTS)
- OpenCV (tested with 2.4.8)


###**Build & Run**

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
