/*
 * File:   RosServerWs_main.cpp
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: This is a example of how ros_ip_transform can be used
 *                   to convert ROSTopic --> TCP/IP.
 *
 * Created September 17, 2015 at 6:00pm
 */


#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>

#include <QCoreApplication>

#include <iostream>
#include <string>
#include <cstdlib>

#include "RosServerWs.h"

using namespace ros;
using namespace std;

RosServerWs server(1234);

void callback(const std_msgs::String::ConstPtr& msg)
{
    server.publishWs(msg);
}


int main(int argc, char **argv)
{
    init(argc, argv, "RosServerWs");
    ROS_INFO("Starting RosServerWs");

    //QCoreApplication app(argc, argv);
    
    NodeHandle nh;
    Subscriber sub = nh.subscribe<std_msgs::String>(/*"/usb_cam/image_raw"*/"/camera/rgb/image_rect_color", 10, callback);

    server.connect2Client(50000);
    //ros::spin();

    return EXIT_SUCCESS;//app.exec();
}
