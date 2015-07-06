/*
 * File:   RosClient.h
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: 
 *
 * Created July 6, 2015 at 10:30
 */


#ifndef ROS_CLIENT_H
#define ROS_CLIENT_H

#include <ros/ros.h>
#include <ros/console.h>

#include <sensor_msgs/Image.h>

#include <opencv/cv.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <assert.h>

#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>

using namespace ros;
using namespace cv;
using namespace std;

class RosClient
{   
    private:
        Publisher* pub;
        int sokt;
        string serverIPStr;
        char* serverIP;
        int serverPort;
        struct sockaddr_in serverAddr;
        socklen_t addrLen;
        
    public:
        RosClient();
        void callback(const sensor_msgs::ImageConstPtr& image);
        Publisher* getPublisher();
        ~RosClient();

};


#endif /* ROS_CLIENT_H */
