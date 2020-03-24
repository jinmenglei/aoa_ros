#include "aoa_ros.h"
#include "aoa_ros/aoa_msg.h"

bool AOA_ros::WriteToUart(unsigned char*)
{
	return true;
}
AOA_ros::AOA_ros()
{
    
    /* Get Luncher file define value */
    ros::NodeHandle nh_private("~");
   
    nh_private.param<std::string>("serial_port", m_strUsart_ports, "/dev/aoa_ros"); 
    nh_private.param<int>("serial_baudrate", m_nBaud_rate, 115200); 
   

    m_pAOA_pub = m_hNodeAOA.advertise<aoa_ros::aoa_msg>("/AOA_report_date", 1000);
}
bool AOA_ros::OpenSerial(void)
{
    try
    {           
        m_Robot_Serial.setPort(m_strUsart_ports);
        m_Robot_Serial.setBaudrate(m_nBaud_rate);
        serial::Timeout to = serial::Timeout::simpleTimeout(2000);
        m_Robot_Serial.setTimeout(to);
        m_Robot_Serial.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("[OpenSerial] Unable to open port ");
        return false;
    }

    if(m_Robot_Serial.isOpen())
    {
        ROS_INFO_STREAM("[OpenSerial] Serial Port opened");
        return true;
    }
    else
    {
        ROS_INFO_STREAM("[OpenSerial] Serial Port open fail");
        return false;
    }
}
bool AOA_ros::ReadFromUart(void)
{
    AOA_Serial_Data_Union Reciver_data;
    //Reciver_data.clear();
    memset(&Reciver_data,0,sizeof(AOA_Serial_Data_Union));
    unsigned char RosReadSerialBuffer[1];
    std_msgs::Int32MultiArray  AOA_msg;
    aoa_ros::aoa_msg aoa_data;
    float angle_f = 0.0;
    int angle_n = 0;
    
    
    if(m_Robot_Serial.available())
    { 
        //ROS_INFO_STREAM("Reading from serial port\n"); 
        m_Robot_Serial.read(Reciver_data.buffer,sizeof(Reciver_data.buffer));
        int start = Reciver_data.AOA_report_date.title.start;


        if (Reciver_data.AOA_report_date.title.start == 0x59 
        && Reciver_data.AOA_report_date.title.len == 0x13
        && Reciver_data.AOA_report_date.type == 0x63
        && Reciver_data.AOA_report_date.end.end == 0x47
        )
        {
            //check key
            aoa_data.rx_rssi_first = Reciver_data.AOA_report_date.rx_rssi_first;
            aoa_data.rx_rssi_all = Reciver_data.AOA_report_date.rx_rssi_all;
            aoa_data.battery = Reciver_data.AOA_report_date.battery;
            aoa_data.keys = Reciver_data.AOA_report_date.keys;
            aoa_data.dist = Reciver_data.AOA_report_date.dist;
            angle_f = Reciver_data.AOA_report_date.angle /1000.0;
            angle_n = angle_f*180/3.14;
            aoa_data.angle = angle_n;
            aoa_data.anchor_status = Reciver_data.AOA_report_date.anchor_status;
            aoa_data.quality = Reciver_data.AOA_report_date.quality;


//            AOA_msg.data.clear();
//            AOA_msg.data.push_back(Reciver_data.AOA_report_date.rx_rssi_first);
//            AOA_msg.data.push_back(Reciver_data.AOA_report_date.rx_rssi_all);
//            AOA_msg.data.push_back(Reciver_data.AOA_report_date.battery);
//            AOA_msg.data.push_back(Reciver_data.AOA_report_date.keys);
//            AOA_msg.data.push_back(Reciver_data.AOA_report_date.dist);
//            angle_f = Reciver_data.AOA_report_date.angle /1000.0;
//            angle_n = angle_f*180/3.14;
//            AOA_msg.data.push_back(angle_n);
//            AOA_msg.data.push_back(Reciver_data.AOA_report_date.anchor_status);
//            AOA_msg.data.push_back(Reciver_data.AOA_report_date.quality);

            m_pAOA_pub.publish(aoa_data);
                    
        }
        else
        {
            m_Robot_Serial.read(RosReadSerialBuffer,sizeof(RosReadSerialBuffer));
            ROS_INFO_STREAM("[ReadFromUart] data is illegle !!!\n");
        }
    }
    else
    {
        //ROS_INFO_STREAM("serial is unavailable !!!\n");
    }

    return false;
}
bool AOA_ros::LoopProcess(void)
{
	
	ros::Rate loop_rate(100);

	while (ros::ok())
	{
		//main logic

		//read urat
		ReadFromUart();

		ros::spinOnce();
		loop_rate.sleep();
	}

	return true;
}
AOA_ros::~AOA_ros()
{
	//do nothing
}
int main(int argc, char *argv[])
{
	//init
	ros::init(argc, argv, "AOA_ros");
	
	//creater
	AOA_ros AOA_ros_control;
	
	//open serial
	if (!AOA_ros_control.OpenSerial())
	{
		return false;
	}
	
	//go to main loop
	AOA_ros_control.LoopProcess();



	return 0;

}






