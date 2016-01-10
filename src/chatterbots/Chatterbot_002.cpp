/**
 * File:   Chatterbot_2.h
 * Module: ros_ip_transform
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: This is developed to test the other files.  It publishes messages in a loop.
 *
 * Created: 1/01/2016
 * Last Modified: 1/05/2016
 */
 


#include <ros/ros.h>
#include <std_msgs/String.h>

#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "chatterbot_002");
    
    ros::NodeHandle nh;
    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("troup_001/robot_002/chatter", 1);
    
    ros::Rate loop_rate(1); //1 hz
    
    //int count = 0;
    while(ros::ok() )
    {
        std_msgs::String msg;
        stringstream ss;
        ss << "I am robot_002";//<< count;
        msg.data = ss.str();
        ROS_INFO("%s", msg.data.c_str() );
        chatter_pub.publish(msg);
        
        ros::spinOnce();
        
        loop_rate.sleep();
        //count++;
    }
    
    return 0;
}
