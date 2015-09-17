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
#include <sensor_msgs/Image.h>

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
    QObject::connect(&client, &RosClientWs::signalClosed, &app, &QCoreApplication::quit);

    return app.exec();
}
