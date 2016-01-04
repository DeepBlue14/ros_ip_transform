#include "RqtSpinner.h"


RqtSpinner::RqtSpinner() :
            shutdown_required(false),
            thread(&RqtSpinner::spin, *this)
{
    ;
}


void RqtSpinner::spin()
{
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("chatter", 10, &RqtSpinner::callback, this);
    
    
    ros::Rate loop(10);
    sleep(1);
    while ( ros::ok() && !shutdown_required )
    {
        ros::spinOnce();
        loop.sleep();
        ROS_INFO("Spinning!");
    }
}


void RqtSpinner::callback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]", msg->data.c_str() );
}


RqtSpinner::~RqtSpinner()
{
    shutdown_required = true;
    thread.join();
}
