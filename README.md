aoa ros

ardent 版本使用 ament build 编译
使用到 串口包 serial
```shell script
sudo apt install ros-melodic-serial
# add cmake path
echo "export PATH=$PATH:/opt/ros/melodic" >> ~/.bashrc
# add ld path
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/ros/melodic/lib" >> ~/.bashrc

要把so复制过去，不然得改PATH，没必要

``` 
 不然会报错


