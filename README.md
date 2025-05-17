# driverDevlopment

##PART 1
ldd.c file is writen proc virtual memmory devlopment how to do read write with that.

commands:
make
sudo insmod ldd.ko 
sudo echo "hii: my name is debashis\n are you doing good because i am good hear\n" > /proc/debashis 
sudo dmesg 
cat /proc/debashis 
sudo rmmod ldd.ko 
make
sudo insmod ldd.ko 
sudo echo "hii: my name is debashis\n are you doing good because i am good hear\n" > /proc/debashis

ref: pyjama youtube linux device driver , https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-part-3-passing-arguments-to-device-driver/

##PART2
ldd_arg_pass.c is written to pass the argument of variable in /sys/module/

Now I’m going to check module_param_cb() is whether calling that handler function or not. For that, I need to change the variable in sysfs. You can write that variable in two ways.

sudo sh -c "echo 13 > /sys/module/hello_world_module/parameters/cb_valueETX"
Type sudo su. Then enter the password if it asks. Then do echo 13 > /sys/module/hello_world_module/parameters/cb_valueETX

ref page: https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-part-3-passing-arguments-to-device-driver/
