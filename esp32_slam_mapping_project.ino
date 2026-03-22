#include <WiFi.h>
#include  <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <ESP32Servo.h>


const char* ssid = "MONEY_IS_GOD_2GHZ";         // Your Wi-Fi network SSID
const char* password = "abrakadabra123"; // Your Wi-Fi network password
const char* serverIP = "192.168.0.113"; // The IP address of your PC running Processing
const uint16_t serverPort = 5204;      // The port you used in the Processing sketch

WiFiClient client;

#define maximum_distance  200

char buffer[120]; // Ensure the buffer is large enough for the final string

//sensor pins
#define trig_pin  17 //analog input 1
#define echo_pin 16 //analog input 2


int count_increment =true;

const byte MOTOR_A = 18;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 19;  // Motor 1 Interrupt Pin - INT 0 - Left Motor

// Constant for steps in disk
const float stepcount = 20.00;  // 20 Slots in disk, change if different

// Constant for wheel diameter
const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different

// Integers for pulse counters
volatile int counter_A = 0;
volatile int counter_B = 0;

const int sensorPin3 = 22; // GPIO Pin
const int sensorPin4 = 23; // GPIO Pin
bool lastState3 = HIGH;
bool lastState4 = HIGH;
int objectCount3 = 0;
int objectCount4 = 0;
bool currentState3;
bool currentState4;

int state =1;
int dir =-1;

const int step_count =20;

int servoPin = 13; // GPIO 18
NewPing sonar(trig_pin,  echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo  name

int enA = 14;  // ENA pin
int in1 = 27;  // IN1 pin
int in2 = 26;  // IN2 pin

// Motor B connections
int enB = 32;  // ENB pin
int in3 = 33;  // IN3 pin
int in4 = 25;  // IN4 pin

boolean goesForward = false;
int distance = 100;
int pwm1 =80;
int pwm2 =200;

// Interrupt Service Routines

// Motor A pulse count ISR
void ISR_countA()  
{
  

  counter_A++;  // increment Motor A counter value

} 

// Motor B pulse count ISR
void ISR_countB()  
{
  counter_B++;  // increment Motor B counter value

}

String boolToString(bool value) {
  if (value) {
    return "true";
  } else {
    return "false";
  }
}

// Function to convert from centimeters to steps
int CMtoSteps(float cm) {

  int result;  // Final calculation result
  float circumference = (wheeldiameter * 3.14) / 10; // Calculate wheel circumference in cm
  float cm_step = circumference / stepcount;  // CM per Step
  
  float f_result = cm / cm_step;  // Calculate result as a float
  result = (int) f_result; // Convert to an integer (note this is NOT rounded)
  
  return result;  // End and return result

}

// Function to Move Forward
void MoveForward(int steps, int mspeed) 
{


  Serial.println("Move Forward with steps");
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A forward
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);

   // Set Motor B forward
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   
   // Go forward until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 0);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 0);
    }
   }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}

// Function to Move in Reverse
void MoveReverse(int steps, int mspeed) 
{
  


  Serial.println("Move Reverse with steps");
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Set Motor B reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   
   // Go in reverse until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 0);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 0);
    }
    }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}

// Function to Spin Right
void SpinRight(int steps, int mspeed) 
{
   dir =0; // direction right

if(state == 0 && dir ==0) //si & r
{
  state =1; //is
}

else if(state == 1 && dir ==0) // is & r 
{
  state =2; // sd
}

else if(state == 2 && dir ==0) //sd & r
{
  state =3;
}

else if(state == 3 && dir ==0) //ds & r
{
   state =0;
}

  
 
  Serial.println("Spin Right");
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
   
   // Go until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 0);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 0);
    }
   }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}

// Function to Spin Left
void SpinLeft(int steps, int mspeed) 
{
  dir =1; // direction left


  if(state == 0 && dir ==1) // si & l
{
 state =3; //ds
}
else if(state == 1 && dir ==1) // is & l
{
   state =0; //si
}
else if(state == 2 && dir ==1) // sd & l
{
   state =1;
}
else if(state == 3 && dir ==1) // ds & l
{
   state =2;
}


  Serial.println("Spin Left");
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Set Motor B reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   
   // Go until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 0);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 0);
    }
  }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}

void moveForward(){

   analogWrite(enA, pwm1); // 100 is slower than 255
    analogWrite(enB, pwm1); // 100 is slower than 255
   Serial.println("move forward");

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(in1,  HIGH);
    digitalWrite(in3, HIGH);
  
    digitalWrite(in2,  LOW);
    digitalWrite(in4, LOW); 
  

  
  }
}

void moveBackward(){
   analogWrite(enB, pwm1); // 100 is slower than 255
    analogWrite(enA, pwm1); // 100 is slower than 255
   Serial.println("move backward");

  goesForward=false;


  digitalWrite(in2, HIGH);
  digitalWrite(in4,  HIGH);
  
  digitalWrite(in1, LOW);
  digitalWrite(in3,  LOW);
}

void moveStop(){
  Serial.println("move stop");
  
  digitalWrite(in1,  LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3,  LOW);
  digitalWrite(in4, LOW);
}
  
int  lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance =  readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int  lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int  readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void sensor_counter()
{
  currentState3 = digitalRead(sensorPin3);
  currentState4 = digitalRead(sensorPin4);


     // Detect falling edge (High to Low transition)
  if (currentState3 == LOW && lastState3 == HIGH || (currentState4 == LOW && lastState4 == HIGH)) {


    if(state ==0)
    {
     objectCount4 = objectCount4 + step_count;
    }
    else if(state ==1)
    {
      objectCount3 = objectCount3 + step_count;
    }
    else if(state ==2)
    {
     objectCount4 =  objectCount4 - step_count;
    }
     else if(state ==3)
    {
     objectCount3 = objectCount3 - step_count;
    }



  
 
    delay(100); // Simple Debounce
  }
  lastState3 = currentState3;
  lastState4 = currentState4;



 sprintf(buffer, "%d,%d,%d,%d", dir, state, objectCount3, objectCount4);

  // Print the formatted string to the serial monitor
  Serial.println(buffer);

  

  
}


void setup() 
{
  Serial.begin(115200);



   Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to the Processing server
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server!");
  } else {
    Serial.println("Connection to server failed!");
  }

  ESP32PWM::allocateTimer(0);

  
  servo_motor.attach(servoPin); //our servo pin

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(sensorPin3, INPUT); // Set as Input
  pinMode(sensorPin4, INPUT); // Set as Input


  // Attach the Interrupts to their ISR's
  attachInterrupt(digitalPinToInterrupt (MOTOR_A), ISR_countA, RISING);  // Increase counter A when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR_B), ISR_countB, RISING);  // Increase counter B when speed sensor pin goes High
  
  // Test Motor Movement  - Experiment with your own sequences here  
 /*
  MoveForward(CMtoSteps(50), 80);  // Forward half a metre at 255 speed
  delay(1000);  // Wait one second
  MoveReverse(10, 80);  // Reverse 10 steps at 255 speed
  delay(1000);  // Wait one second
  MoveForward(10, 80);  // Forward 10 steps at 150 speed
  delay(1000);  // Wait one second
  MoveReverse(CMtoSteps(25.4),80);  // Reverse 25.4 cm at 200 speed
  delay(1000);  // Wait one second
  SpinRight(20, 200);  // Spin right 20 steps at 255 speed
  delay(1000);  // Wait one second
  SpinLeft(60, 200);  // Spin left 60 steps at 175 speed
  delay(1000);  // Wait one second
  MoveForward(1, 80);  // Forward 1 step at 255 speed

  */
  
  
} 


void loop()
{
  // Put whatever you want here!

    int distanceRight = 0;
  int  distanceLeft = 0;
  delay(50);

  if (distance <= 30){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft  = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      SpinRight(20, 200);  // Spin right 20 steps at 255 speed
      moveStop();
    }
    else{
      SpinLeft(20, 200);  // Spin left 60 steps at 175 speed
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
  sensor_counter();

  send_data_wifi(buffer);
  
}


void send_data_wifi(char *data) {
  if (client.connected()) {
    // Send data to the Processing server
    // For example, send a random number or sensor reading
    
    client.println(data); // client.print() methods are supported
  
  } else {
    Serial.println("Client disconnected. Reconnecting...");
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Reconnected to server!");
    } else {
      Serial.println("Reconnection failed!");
     
    }
  }
}
