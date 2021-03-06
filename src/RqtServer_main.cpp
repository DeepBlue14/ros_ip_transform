/**
 * File:   RqtServer_main.cpp
 * Module: ros_ip_transforms
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: main() method for the websocket server.
 *
 * TODO: use global variable/buffer to pass data between threads?
 *       Or have spinner call RqtServer slot directly?
 *
 * Created: 1/01/2016
 * Last Modified: 1/03/2016
 */

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>

#include <QtCore/QCoreApplication>

#include "RqtServer.h"
#include "RqtSpinner.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "RqtServer");
    ros::NodeHandle node;

    QCoreApplication app(argc, argv);
    RqtServer server(1234);
    RqtSpinner spinner(&server);
    int result = app.exec();

    return result;
}
