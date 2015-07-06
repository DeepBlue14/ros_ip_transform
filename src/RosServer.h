#ifndef ROS_SERVER_H
#define ROS_SERVER_H

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
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h> 

using namespace ros;
using namespace cv;
using namespace std;

class RosServer
{   
    private:
        int localSocket;
        int remoteSocket;
        int port;
        struct sockaddr_in localAddr,
                           remoteAddr;
        int addrLen;
        Publisher* pub;
        
    public:
        RosServer();
        void callback(const sensor_msgs::ImageConstPtr& image);
        Publisher* getPublisher();
        ~RosServer();

};


#endif /* ROS_SERVER_H */
