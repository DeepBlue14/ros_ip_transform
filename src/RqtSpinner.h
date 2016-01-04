/**
 * File:   RqtSpinner.h
 * Module: ros_ip_transform
 * Author: James Kuczynski
 * Email: jkuczyns@cs.uml.edu
 * File Description: 
 *
 * Created: 1/01/2016
 * Last Modified: 1/03/2016
 */


//#include <QtGui>
//#include <QApplication>
#include <ros/ros.h>
#include <std_msgs/String.h>

#include <ecl/threads/thread.hpp> // or boost threads if you prefer

#include "RqtServer.h"

class RqtSpinner
{    
public:
    RqtSpinner();
    void spin();
    void callback(const std_msgs::String::ConstPtr& msg);
    ~RqtSpinner();
        
private:
    bool shutdown_required;
    ecl::Thread thread; // similarly, a boost thread
};
