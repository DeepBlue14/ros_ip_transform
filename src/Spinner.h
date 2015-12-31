//#include <QtGui>
//#include <QApplication>
#include <ros/ros.h>

#include <ecl/threads/thread.hpp> // or boost threads if you prefer

#include "RqtServer.h"

class Spinner
{
    private:
        bool shutdown_required;
        ecl::Thread thread; // similarly, a boost thread 
        
    public:
        Spinner();
        void spin();
        ~Spinner();
};
