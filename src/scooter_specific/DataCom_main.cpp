#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <iostream>
#include <string>
#include <cstdlib>

#include "DataCom.h"

using namespace ros;
using namespace std;

DataCom dataCom;

void callback(const sensor_msgs::ImageConstPtr& msg)
{
    dataCom.publishTcp(msg);
}


int main(int argc, char **argv)
{
    init(argc, argv, "DataCom");

    ROS_INFO("Starting DataCom");

    NodeHandle nh;
    Subscriber sub = nh.subscribe<sensor_msgs::Image>(/*"/usb_cam/image_raw"*/"/camera/rgb/image_rect_color", 10, callback);
    Publisher* mainsPub = dataCom.getPublisher();
    *mainsPub = nh.advertise<geometry_msgs::Point>("/scooter/geometry_msgs/pixel_point", 10);

    dataCom.connect2Client(50001);
    ros::spin();


    return EXIT_SUCCESS;
}
