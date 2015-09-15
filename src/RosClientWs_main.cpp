/*
 * File:   RosClient_main.cpp
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: This is a example of how ros_ip_transform can be used
 *                   to convert TCP/IP --> ROSTopic.
 *
 * Created July 6, 2015 at 10:30
 */
 

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <iostream>
#include <string>
#include <cstdlib>

#include "RosClientWs.h"

using namespace ros;
using namespace std;


int main(int argc, char **argv)
{
    init(argc, argv, "RosClientWs");

    ROS_INFO("Starting RosClientWs");

    RosIpT::RosClientWs rosClientWs;
    NodeHandle nh;
    Publisher* mainsPub = rosClientWs.getPublisher();
    *mainsPub = nh.advertise<sensor_msgs::Image>("/test/rgb/image_rect_color", 10);
    
    rosClientWs.connect2Server("127.0.0.1", 50000);

    rosClientWs.spinTcp();
    

    return EXIT_SUCCESS;
}
