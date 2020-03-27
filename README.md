aoa ros

安装串口包
```
sudo apt install ros-kinetic-serial
```
设置串口连接

这边使用的是CH340
```
sudo ./creat_AOA_ros_udev.sh
```

启动launch

```
roslaunch aoa_ros aoa_ros.launch
```

msg_type
```
std_msgs/Header header
int32 rx_rssi_first
int32 rx_rssi_all
int32 battery
int32 keys
int32 dist
int32 angle
int32 anchor_status
int32 quality

```
topicname
```
/AOA_report_date
```

结果：
```
header: 
  seq: 41
  stamp: 
    secs: 0
    nsecs:         0
  frame_id: ''
rx_rssi_first: -82
rx_rssi_all: -78
battery: 13
keys: 255
dist: 35
angle: 5
anchor_status: 128
quality: 255
---
header: 
  seq: 42
  stamp: 
    secs: 0
    nsecs:         0
  frame_id: ''
rx_rssi_first: -82
rx_rssi_all: -78
battery: 13
keys: 255
dist: 36
angle: 5
anchor_status: 128
quality: 255
---
header: 
  seq: 43
  stamp: 
    secs: 0
    nsecs:         0
  frame_id: ''
rx_rssi_first: -83
rx_rssi_all: -78
battery: 13
keys: 255
dist: 37
angle: 5
anchor_status: 128
quality: 255
```
