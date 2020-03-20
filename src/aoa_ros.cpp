#include "aoa_ros.h"


bool AOA_ros::WriteToUart(unsigned char *) {
    return true;
}

AOA_ros::AOA_ros() {

    /* Get Luncher file define value */
    m_hNodeAOA = Node::make_shared("aoa_ros");

    m_strUsart_ports = "/dev/aoa_ros";
    m_hNodeAOA->get_parameter("serial_port", m_strUsart_ports);
    m_nBaud_rate = 115200;
    m_hNodeAOA->get_parameter("serial_baudrate", m_nBaud_rate);


    m_pAOA_pub = m_hNodeAOA->create_publisher<std_msgs::msg::Int32MultiArray>("AOA_report_date", 7);

}

bool AOA_ros::OpenSerial(void) {
    try {
        m_Robot_Serial.setPort(m_strUsart_ports);
        m_Robot_Serial.setBaudrate(m_nBaud_rate);
        serial::Timeout to = serial::Timeout::simpleTimeout(2000);
        m_Robot_Serial.setTimeout(to);
        m_Robot_Serial.open();
    }
    catch (serial::IOException &e) {

        RCLCPP_ERROR(m_hNodeAOA->get_logger(), "[OpenSerial] Unable to open port ");
        return false;
    }

    if (m_Robot_Serial.isOpen()) {
        RCLCPP_INFO(m_hNodeAOA->get_logger(), "[OpenSerial] Serial Port opened");
        return true;
    } else {
        RCLCPP_ERROR(m_hNodeAOA->get_logger(), "[OpenSerial] Serial Port open fail");
        return false;
    }
}

bool AOA_ros::ReadFromUart(void) {
    AOA_Serial_Data_Union Reciver_data;
    //Reciver_data.clear();
    memset(&Reciver_data, 0, sizeof(AOA_Serial_Data_Union));
    unsigned char RosReadSerialBuffer[1];
    std_msgs::msg::Int32MultiArray AOA_msg;
    float angle_f = 0.0;
    int angle_n = 0;


    if (m_Robot_Serial.available()) {
        //ROS_INFO_STREAM("Reading from serial port\n"); 
        m_Robot_Serial.read(Reciver_data.buffer, sizeof(Reciver_data.buffer));


        if (Reciver_data.AOA_report_date.title.start == 0x59
            && Reciver_data.AOA_report_date.title.len == 0x13
            && Reciver_data.AOA_report_date.type == 0x63
            && Reciver_data.AOA_report_date.end.end == 0x47
                ) {
            //check key
            AOA_msg.data.clear();
            AOA_msg.data.push_back(Reciver_data.AOA_report_date.rx_rssi_first);
            AOA_msg.data.push_back(Reciver_data.AOA_report_date.rx_rssi_all);
            AOA_msg.data.push_back(Reciver_data.AOA_report_date.battery);
            AOA_msg.data.push_back(Reciver_data.AOA_report_date.keys);
            AOA_msg.data.push_back(Reciver_data.AOA_report_date.dist);
            angle_f = Reciver_data.AOA_report_date.angle / 1000.0; // NOLINT(bugprone-narrowing-conversions)
            angle_n = angle_f * 180 / 3.14;
            AOA_msg.data.push_back(angle_n);
            AOA_msg.data.push_back(Reciver_data.AOA_report_date.anchor_status);
            AOA_msg.data.push_back(Reciver_data.AOA_report_date.quality);

            m_pAOA_pub->publish(AOA_msg);

        } else {
            m_Robot_Serial.read(RosReadSerialBuffer, sizeof(RosReadSerialBuffer));
            RCLCPP_ERROR(m_hNodeAOA->get_logger(), "[ReadFromUart] data is illegle !!!\n");
        }
    } else {
        //ROS_INFO_STREAM("serial is unavailable !!!\n");
    }

    return false;
}

bool AOA_ros::LoopProcess(void) {

    rclcpp::Rate loop_rate(100);

    while (rclcpp::ok()) {
        //main logic

        //read urat
        ReadFromUart();

        rclcpp::spin_some(m_hNodeAOA);
        loop_rate.sleep();
    }

    return true;
}

AOA_ros::~AOA_ros() {
    //do nothing
}

int main(int argc, char *argv[]) {
    //init
    rclcpp::init(argc, argv);

    //creater
    AOA_ros AOA_ros_control;

    //open serial
    if (!AOA_ros_control.OpenSerial()) {
        return 0;
    }

    //go to main loop
    AOA_ros_control.LoopProcess();


    return 0;

}






