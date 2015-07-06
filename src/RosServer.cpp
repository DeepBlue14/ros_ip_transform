#include "RosServer.h"


RosServer::RosServer()
{
    pub = new Publisher();
    localSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(localSocket == -1)
    {
        perror("socket() call failed!!");
    }
    port = 50000;
    addrLen = sizeof(struct sockaddr_in);
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = INADDR_ANY;
    localAddr.sin_port = htons(port);
    
    if(bind(localSocket, (struct sockaddr*)&localAddr, sizeof(localAddr)) < 0)
    {
        perror("Can't bind() socket");
        exit(1);
    }
    
    listen(localSocket, 1);
    
    cout << "Waiting for connections...\n"
              << "Server Port: " << port << endl;
    
    remoteSocket = accept(localSocket, (struct sockaddr *)&remoteAddr, (socklen_t*)&addrLen);
    if(remoteSocket < 0)
    {
        perror("Accept failed!");
        exit(1);
    }
    cout << "Connection accepted" << endl;
    
}


void RosServer::callback(const sensor_msgs::ImageConstPtr& input)
{
    //convert to OpenCV type- - - - - - - - - - - - - - - - - -
    cv_bridge::CvImagePtr cv_ptr;
    cv::Mat img, imgGray;

    try
    {
        cv_ptr = cv_bridge::toCvCopy(input/*, sensor_msgs::image_encodings::RGB16*//*RGB8*/); // TYPE_32SC4
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what() );
    }
    
    img = cv_ptr->image;
    cv::imshow("Server", img);
    cv::waitKey(3);
    
    imgGray = img.clone();
    cvtColor(img, imgGray, CV_BGR2GRAY);
    cv::imshow("About To Send", imgGray);
    cv::waitKey(3);
    
    int imgSize = imgGray.total() * imgGray.elemSize();
    int bytes = 0;
    int key;
    
    if((bytes = send(remoteSocket, imgGray.data, imgSize, 0)) < 0)
    {
        cerr << "bytes = " << bytes << endl;
    }
    
    
    //cv_ptr->image = img;
    //pub->publish(cv_ptr->toImageMsg() );
}


Publisher* RosServer::getPublisher()
{
    return pub;
}


RosServer::~RosServer()
{
    close(remoteSocket);
}
