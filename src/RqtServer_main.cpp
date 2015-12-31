#include <ros/ros.h>

#include <QtCore/QCoreApplication>

#include "RqtServer.h"
#include "Spinner.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "RqtServer");
    ros::NodeHandle node;
    Spinner spinner;

    QCoreApplication app(argc, argv);
    RqtServer server(1234);
    int result = app.exec();

    return result;
}
