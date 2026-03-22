# ESP32 DEV KIT V1 wireless room mapping using ultrasonic sensor ,L298N and speed sensor
map the room using ESP32 dev kit module v1 ,speed sensors, L298N and ultrasonic sensor and plot it wirelessly in Processing IDE. 

**************************************caution *************************************************
please dont try the random codes present in internet for driving the L298N and motors as it has created smoke in my 4 wheeled robot, 
use PWM less than 200 for L298N motor driver so that it doesnt push more current into motors.

The ode present in this random nerd tutorial website has create smoke in my motors as it contains loop to make PWM or duty cycle to 255
https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/

************************************************************************************************
CREDITS TO DRONE BOT WORKSHOP

this project uses esp32 , ultrasonic sensor , speed sensors and 4 wheeled robot for mapping room using processing IDE through WIFI connection.
credits goes to dronebotworkshop website, the youtube video has clear explanation of the code he has written, but the code present in his website 
did not work as he failed to declare outputs in the setup function. so i modified it to make it work.

https://dronebotworkshop.com/robot-car-with-speed-sensors/

https://www.youtube.com/watch?v=oQQpAACa3ac

***************************************************************************************************
HOW TO ASSEMBLED 4 WHEELED ROBOT CHASSIS

https://www.youtube.com/watch?v=2EYv6FJH4ww&list=PLNlGfOpbU1otd4UpPlZKb6BHyrvKKH1et&index=159

pin usage in esp32 dev kit module v1
--------------------------------------
Safe Pins: Almost all GPIOs work, but use safe GPIOs like 4, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33, 34, 35, 36, 39.
Avoid Pins: Avoid 0, 2, 5, 12, 15 (boot constraints) and 6–11 (flash memory).
ISR Best Practices: Keep the ISR function (handleSensor) extremely short. Do not use delay() or Serial.print() inside the ISR.
Trigger Modes: Use RISING (LOW to HIGH) or FALLING (HIGH to LOW) based on how the sensor toggles. 

https://kitsguru.com/collections/robotics-chassis/products/4wd-double-layer-transparent-robot-car-chassis-kit-diy-robotics-platform

https://kitsguru.com/products/speed-measuring-sensor-groove-coupler-module-for-arduino-1?_pos=2&_sid=462693c96&_ss=r

