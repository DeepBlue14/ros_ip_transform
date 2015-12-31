#include "RqtSpinner.h"


RqtSpinner::RqtSpinner() :
            shutdown_required(false),
            thread(&RqtSpinner::spin, *this)
{
    ;
}


void RqtSpinner::spin()
{
    ros::Rate loop(10);
    sleep(1);
    while ( ros::ok() && !shutdown_required )
    {
        ros::spinOnce();
        loop.sleep();
        ROS_INFO("Spinning!");
    }
}


RqtSpinner::~RqtSpinner()
{
    shutdown_required = true;
    thread.join();
}
