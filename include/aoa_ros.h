#ifndef __AOA_ROS_H_
#define __AOA_ROS_H_

#include "std_msgs/msg/int32_multi_array.hpp"
#include <serial/serial.h>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/logger.hpp"

#define PROTOBUFLENGHT      19

using namespace rclcpp;

#pragma pack(1)

__attribute__((aligned(1))) typedef struct
{
    uint16_t  crc16;
    uint8_t    end;
}frame_end_t;

__attribute__((aligned(1))) typedef struct
{
    uint8_t  start;
    uint8_t  len;
}frame_title_t;

__attribute__((aligned(1)))  typedef struct
{
    frame_title_t title;//帧头
    uint8_t type;
    uint8_t seq_num;//帧序号 0~255
    int8_t rx_rssi_first;//保留
    int8_t rx_rssi_all;//保留
    int8_t   battery;//电量
    uint8_t  keys;//按键值
    uint16_t Tag_ID;//标签ID
    uint16_t dist;//距离 单位 cm
    int16_t  angle;//乘以 1000 以后的弧度
    uint8_t  anchor_status;//基站的状态
    uint8_t  quality;//信号质量 1质量差 0质量好
    frame_end_t  end;//帧尾
}AOA_report_t;


typedef union AOA_Serial_Data_Union   
{
    unsigned char buffer[PROTOBUFLENGHT];
    
    AOA_report_t AOA_report_date;
    
}AOA_Serial_Data_Union;



#pragma pack(4)


using namespace std;

class AOA_ros
{
public:
    AOA_ros();
    ~AOA_ros();

    /* Read/Write data from ttyUSB */
    bool ReadFromUart(void);
    bool WriteToUart(unsigned char*);
    bool LoopProcess(void);
    bool OpenSerial(void);
    
    //bool

    serial::Serial m_Robot_Serial; //声明串口对象 
    string m_strUsart_ports;
    int m_nBaud_rate;

private:
    shared_ptr<Node> m_hNodeAOA;
    Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr m_pAOA_pub;
};


#endif
