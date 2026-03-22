# esp32 room mapping using ultrasonic sensor ,L298N and speed sensor
map the room using ESP32 and ultrasonic sensor and plot it in Processing IDE 

**************************************caution *************************************************
please dont try the random codes present in internet for driving the L298N and motors as it has created smoke in my 4 wheeled robot, 
use PWM less than 200 for L298N motor driver so that it doesnt push more current into motors.

The ode present in this random nerd tutorial website has create smoke in my motors as it contains loop to make PWM or duty cycle to 255
https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/

************************************************************************************************


this project uses esp32 , ultrasonic sensor , speed sensors and 4 wheeles robot for mapping room using processing IDE through WIFI connection.
credits goes to dronebotworkshop website, the youtube video has ckear explanation of the code he has written, but the code present in his website 
did nt work as he failed to declare outputs in the setup function. so i modified it to make it work.

https://dronebotworkshop.com/robot-car-with-speed-sensors/
https://www.youtube.com/watch?v=oQQpAACa3ac


https://kitsguru.com/collections/robotics-chassis/products/4wd-double-layer-transparent-robot-car-chassis-kit-diy-robotics-platform

https://kitsguru.com/products/speed-measuring-sensor-groove-coupler-module-for-arduino-1?_pos=2&_sid=462693c96&_ss=r

