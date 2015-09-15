/*
 * File:   RosClientWs.h
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: This program converts OpenCV matrix to sensor_msgs::Image,
 *                   which recieves then sends over a TCP/IP connection and 
 *                   publishes to a ros topic.  This allows it to be easily
 *                   utalized by a client system running
 *                   Windows, Linux, OS X, FreeBSD, NetBSD, OpenBSD,
 *                   Android, IOS, Maemo, or BlackBerry, and using any
 *                   language supported by OpenCV (C/C++, Java, Android,
 *                   Python, and MATLAB/OCTAVE, as well as partial
 *                   functionality for C#, Perl, Ruby, and Ch.
 *
 * Created July 6, 2015 at 10:30
 */


#ifndef ROS_CLIENT_WS_H
#define ROS_CLIENT_WS_H

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

#include <boost/thread.hpp>

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

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

#include "RosIpT.h"

using namespace ros;
using namespace cv;
using namespace std;
using namespace RosIpT;

class RosIpT::RosClientWs
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
        RosClientWs();
        bool connect2Server(string address = "127.0.0.1", int port = 50000);
        void spinTcp(int spinRate = 100);
        void subscribe(int spinRate);
        void closeConnection();
        Publisher* getPublisher();
        ~RosClientWs();

};


#endif /* ROS_CLIENT_WS_H */
