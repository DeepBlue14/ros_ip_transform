#include "Spinner.h"


Spinner::Spinner() :
            shutdown_required(false),
            thread(&Spinner::spin, *this)
{
    ;
}


void Spinner::spin()
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


Spinner::~Spinner()
{
    shutdown_required = true;
    thread.join();
}
