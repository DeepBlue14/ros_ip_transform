#include "DataCom.h"


int DataCom::m_comm_fd;


DataCom::DataCom()
{
    m_count = 0;
    pub = new Publisher();
}


bool DataCom::connect2Client(int port)
{
    int listen_fd, comm_fd;
 
    struct sockaddr_in servaddr;
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero( &servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(50001);
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listen_fd, 10);
 
    m_comm_fd = comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
    cout << "Successfully connected to client" << endl;
    
    return true;
}


void DataCom::publishTcp(const sensor_msgs::ImageConstPtr& msg)
{
    char str[100];
    bzero(str, 100);
    cout << "blocking before read..." << endl;
    ssize_t rretn = read(m_comm_fd, str, 100);
    
    int delimCounter = 0;
    string xStr, yStr;
    int x = 0, y = 0;
    
    //extract chars from string
    for(size_t i = 0; i < 100; i++)
    {
        if(str[i] == '|' && delimCounter == 0)
        {
            delimCounter++;
        }
        else if(str[i] == '|' && delimCounter == 1)
        {
            delimCounter++;
        }
        else if(str[i] == '|' && delimCounter == 2)
        {
            break;
        }
        else if(str[i] != '|' && delimCounter == 1)
        {
            xStr += str[i];
        }
        else if(str[i] != '|' && delimCounter == 2)
        {
            yStr += str[i];
        }
            
    }
    
    x = atoi(xStr.c_str());
    y = atoi(yStr.c_str());
    cout << "x: " << x << ", y: " << y << endl;
    
    //if(m_count > 10) // Reject the first 10, since some of the first images may contain discolorations
    //{
        cv_bridge::CvImagePtr cv_ptr;
        cv::Mat img, imgGray;

        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
        }
        catch(cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what() );
        }
    
        img = cv_ptr->image;
        //cv::imshow("Server", img);
        //cv::waitKey(3);
    
        imgGray = img.clone();
        //cvtColor(img, imgGray, CV_BGR2GRAY);
        //cv::imshow("About To Send", imgGray);
        //cv::waitKey(3);
    
        int imgSize = imgGray.total() * imgGray.elemSize();
        //cout << "sending: " << imgSize << " bytes" << endl;
        int bytes = 0;
        int key;
    
        if((bytes = send(m_comm_fd/*remoteSocket*/, imgGray.data, imgSize, 0)) < 0)
        {
            cerr << "bytes = " << bytes << endl;
        }
        else
        {
            cout << "successfully sent message" << endl;
        }
    /*}
    else
    {
        m_count++;
        cout << "Skipping tcp transfer" << endl;
    }*/
    //ssize_t wretn = write(m_comm_fd, str2, 

}


Publisher* DataCom::getPublisher()
{
    return pub;
}


DataCom::~DataCom()
{
    close(remoteSocket);
}
