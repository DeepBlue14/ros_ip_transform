/**
 * File: 
 * Module: 
 * Author: 
 * Email: 
 * File Description:
 *
 * TODO: use global variable/buffer to pass data between threads?
 *
 * Created: 
 * Last Modified: 
 */

#include <ros/ros.h>

#include <QtCore/QCoreApplication>

#include "RqtServer.h"
#include "RqtSpinner.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "RqtServer");
    ros::NodeHandle node;
    RqtSpinner spinner;

    QCoreApplication app(argc, argv);
    RqtServer server(1234);
    int result = app.exec();

    return result;
}
