#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <iostream>
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
    Subscriber sub = nh.subscribe<sensor_msgs::Image>(/*"/usb_cam/image_raw"*/"/camera/rgb/image_rect_color",
                                                        10,
                                                        &RosClient::callback,
                                                        &rosClient);
    *mainsPub = nh.advertise<sensor_msgs::Image>("/test/rgb/image_rect_color", 10);



    ros::Rate r(100);
    while (ros::ok())
    {
        //libusb_handle_events_timeout(...); // Handle USB events
        ros::spinOnce();                   // Handle ROS events
        r.sleep();
    }
    

    return EXIT_SUCCESS;
}
