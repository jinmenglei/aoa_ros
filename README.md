aoa ros

ardent 版本使用 ament build 编译
使用到 串口包 serial
```shell script
sudo apt install ros-kinetic-serial

sudo cp /opt/ros/kinetic/lib/libserial.so /opt/ros/ardent/lib/

sudo mkdir /opt/ros/ardent/share/serial/

sudo cp /opt/ros/kinetic/share/serial/* /opt/ros/ardent/share/serial/  -rf

``` 
 不然会报错


