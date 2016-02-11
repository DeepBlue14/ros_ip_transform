#include "RqtSpinner.h"


RqtSpinner::RqtSpinner(RqtServer* rqtServer) : shutdown_required(false), thread(&RqtSpinner::spin, *this)
{

    //ros::Publisher* pub = rqtServer->getPublisher();
    
    this->rqtServer = rqtServer;
}


void RqtSpinner::spin()
{
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("/robot_001/update"/*"/troup_001/robot_001/chatter"*/, 10, &RqtSpinner::callback, this);
    ros::Publisher* mainsPub = rqtServer->getPublisher();
    *mainsPub = nh.advertise<std_msgs::String>("/user/chatter", 10);
    
    
    ros::Rate loop(10);
    sleep(1);
    while ( ros::ok() && !shutdown_required )
    {
        ros::spinOnce();
        loop.sleep();
        //ROS_INFO("Spinning!");
    }
}


void RqtSpinner::callback(const std_msgs::String::ConstPtr& msg)
{
    //ROS_INFO("I heard: [%s]", msg->data.c_str() );
    
    rqtServer->messageBridge(msg);
}


void RqtSpinner::setRqtServer(RqtServer* rqtServer)
{
    this->rqtServer = rqtServer;
}


RqtSpinner::~RqtSpinner()
{
    shutdown_required = true;
    thread.join();
}
