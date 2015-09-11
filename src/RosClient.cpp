#include "RosClient.h"


RosClient::RosClient()
{
    pub = new Publisher();
}


bool RosClient::connect2Server(string address, int port)
{
    serverPort = port;
    addrLen = sizeof(struct sockaddr_in);

    if((sokt = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        cerr << "socket() failed" << endl;
    }
    
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(serverPort);
    
    if(connect(sokt, (sockaddr*)&serverAddr, addrLen) < 0)
    {
        cerr << "connect() failed!" << endl;
    }
}


void RosClient::spinTcp(int spinRate)
{
    boost::thread workerThread(&RosClient::subscribe, this, spinRate);
    workerThread.join();
    
    //--------
}


void RosClient::subscribe(int spinRate)
{
    ros::Rate r(spinRate);
    while(ros::ok() )
    {
	    cv_bridge::CvImage cv_ptr;
        cv::Mat img = cv::Mat::zeros(480, 640, CV_8UC(3));
  
        int imgSize = img.total() * img.elemSize();
        unsigned char* iptr = img.data;
        int bytes = 0;
 
        if(!img.isContinuous() )
        {
            img = img.clone();
        }
        cout << "waiting for: " << imgSize << " bytes" << endl; //should be 921600
        cv::namedWindow("Client", 1);
   
        if((bytes = recv(sokt, iptr, imgSize, MSG_WAITALL)) == -1)
        {
            cerr << "recv failed, recieved bytes = " << bytes << endl;
        }
    
        cv::imshow("Client", img);
        cv::waitKey(3);

        cv_ptr.image = img;
        pub->publish(cv_ptr.toImageMsg() );
    }
}


Publisher* RosClient::getPublisher()
{
    return pub;
}


RosClient::~RosClient()
{
    close(sokt);
}
