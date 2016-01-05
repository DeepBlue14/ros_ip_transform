/**
 * File:   RqtSpinner.h
 * Module: ros_ip_transform
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: 
 *
 * Created: 1/01/2016
 * Last Modified: 1/05/2016
 */


#ifndef RQT_SPINNER_H
#define RQT_SPINNER_H

//#include <QtGui>
//#include <QApplication>
#include <ros/ros.h>
#include <std_msgs/String.h>

#include <ecl/threads/thread.hpp> // or boost threads if you prefer

#include "RqtServer.h"

class RqtSpinner
{    

public:
    RqtSpinner(RqtServer* rqtServer);
    void spin();
    void callback(const std_msgs::String::ConstPtr& msg);
    void setRqtServer(RqtServer* rqtServer);
    ~RqtSpinner();
        
private:
    RqtServer* rqtServer;
    bool shutdown_required;
    ecl::Thread thread; // similarly, a boost thread
};

#endif /* RQT_SPINNER_H */
