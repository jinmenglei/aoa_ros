
#ifndef __AOA_ROS_H_
#define __AOA_ROS_H_

#include "aoa_type.h"
#include "std_msgs/Int32MultiArray.h"
#include <serial/serial.h>

using namespace std;

class AOA_ros
{
public:
    AOA_ros();
    ~AOA_ros();

    /* Read/Write data from ttyUSB */
    bool ReadFormUart(void);
    bool WriteToUart(unsigned char*);
    bool LoopProcess(void);
    bool OpenSerial(void);
    
    //bool

    serial::Serial m_Robot_Serial; //声明串口对象 
    string m_strUsart_ports;
    int m_nBaud_rate;
    

private:  
    ros::NodeHandle m_hNodeAOA; 
    ros::Publisher m_pAOA_pub;  
};


#endif


