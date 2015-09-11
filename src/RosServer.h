/*
 * File:   RosServer.h
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: This program converts sensor_msgs::Image to OpenCV matrix,
 *                   which it then sends over a TCP/IP connection.  This allows
 *                   it to be easily recieved and decoded by a client system
 *                   running Windows, Linux, OS X, FreeBSD, NetBSD, OpenBSD,
 *                   Android, IOS, Maemo, or BlackBerry, and using any
 *                   language supported by OpenCV (C/C++, Java, Android,
 *                   Python, and MATLAB/OCTAVE, as well as partial
 *                   functionality for C#, Perl, Ruby, and Ch.
 *
 * Created July 6, 2015 at 10:30
 */


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
        static int m_comm_fd;
        int m_count;
        int localSocket;
        int remoteSocket;
        int port;
        struct sockaddr_in localAddr,
                           remoteAddr;
        int addrLen;
        Publisher* pub;
        
    public:
        RosServer();
        //void callback(const sensor_msgs::ImageConstPtr& image);
        bool connect(int port);
        void publishTcp(const sensor_msgs::ImageConstPtr& msg);
        Publisher* getPublisher();
        ~RosServer();

};


#endif /* ROS_SERVER_H */
