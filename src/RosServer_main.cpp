#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <iostream>
#include <string>
#include <cstdlib>

#include "RosServer.h"

using namespace ros;
using namespace std;

RosServer rosServer;

void callback(const sensor_msgs::ImageConstPtr& msg)
{
    rosServer.publishTcp(msg);
}


int main(int argc, char **argv)
{
    init(argc, argv, "RosServer");

    ROS_INFO("Starting RosServer");

    NodeHandle nh;
    Subscriber sub = nh.subscribe<sensor_msgs::Image>(/*"/usb_cam/image_raw"*/"/camera/rgb/image_rect_color", 10, callback);

    rosServer.connect(50000);
    ros::spin();


    return EXIT_SUCCESS;
}
