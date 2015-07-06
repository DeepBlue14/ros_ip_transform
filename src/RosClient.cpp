#include "RosClient.h"


RosClient::RosClient()
{
    pub = new Publisher();
    serverPort = 50000;
    addrLen = sizeof(struct sockaddr_in);
    cout << "HERE (5)" << endl;
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


void RosClient::callback(const sensor_msgs::ImageConstPtr& input)
{
    //convert to OpenCV type- - - - - - - - - - - - - - - - - -
    cv_bridge::CvImagePtr cv_ptr;
    cv::Mat img = Mat::zeros(480, 640, CV_8UC1);

    try
    {
        ;//cv_ptr = cv_bridge::toCvCopy(input/*, sensor_msgs::image_encodings::RGB16*//*RGB8*/);
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what() );
    }
    
    ;//img = cv_ptr->image;
    //cv::imshow("Initial Image", img);
    //cv::waitKey(3);
    
    
    int imgSize = img.total() * img.elemSize();
    uchar *iptr = img.data;
    int bytes = 0;
    
    if(!img.isContinuous() )
    {
        img = img.clone();
    }
    
    namedWindow("Client", 1);
    
    if((bytes = recv(sokt, iptr, imgSize, MSG_WAITALL)) == -1)
    {
        cerr << "recv failed, recieved bytes = " << bytes << endl;
    }
    
    cv::imshow("Client", img);
    cv::waitKey(3);
    
    //cv_ptr->image = img;
    //pub->publish(cv_ptr->toImageMsg() );
}


Publisher* RosClient::getPublisher()
{
    return pub;
}


RosClient::~RosClient()
{
    close(sokt);
}
