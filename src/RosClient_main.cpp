#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <iostream>
#include <string>
#include <cstdlib>

#include "RosClient.h"

using namespace ros;
using namespace std;


int main(int argc, char **argv)
{
    init(argc, argv, "RosClient");

    ROS_INFO("Starting RosClient");

    RosClient rosClient;
    NodeHandle nh;
    Publisher* mainsPub = rosClient.getPublisher();
    *mainsPub = nh.advertise<sensor_msgs::Image>("/test/rgb/image_rect_color", 10);
    
    rosClient.connect2Server("127.0.0.1", 50000);

    rosClient.spinTcp();
    

    return EXIT_SUCCESS;
}
