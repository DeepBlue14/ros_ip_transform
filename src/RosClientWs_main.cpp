/*
 * File:   RosClient_main.cpp
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: This is a example of how ros_ip_transform can be used
 *                   to convert TCP/IP --> ROSTopic.
 *
 * Created September 17, 2015 at 6:00pm
 */
 

#include <ros/ros.h>
#include <std_msgs/String.h>

#include <QCoreApplication>

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

    QCoreApplication app(argc, argv);

    RosClientWs client(QUrl(QStringLiteral("ws://localhost:1234")) );
    client.connect2Server(&client, &app);
    
    NodeHandle nh;
    Publisher* mainsPub = client.getPublisher();
    *mainsPub = nh.advertise<std_msgs::String>("/test/std_msgs/chatter", 10);
    
    client.spinWs();

    return EXIT_SUCCESS;
}
