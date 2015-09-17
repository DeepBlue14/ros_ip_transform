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
#include <sensor_msgs/Image.h>

#include <QCoreApplication>

#include <iostream>
#include <string>
#include <cstdlib>

#include "RosServerWs.h"

using namespace ros;
using namespace std;

int main(int argc, char **argv)
{
    init(argc, argv, "RosServerWs");
    ROS_INFO("Starting RosServerWs");

    QCoreApplication app(argc, argv);
    RosServerWs server(1234);
    
    NodeHandle nh;
    //Subscriber sub = nh.subscribe<sensor_msgs::Image>(/*"/usb_cam/image_raw"*/"/camera/rgb/image_rect_color", 10, callback);

    //rosServer.connect2Client(50000);
    //ros::spin();

    return app.exec();
}
