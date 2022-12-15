/*
The purpose of this program is to be able to use collision avoidance to control the robot car.
Using the ultrasonic sensor it dectect at set distance when there is obstacle.
Each movement is detemined whether there is an obstacle in its path or not.
*/

#include <arduino.h>
#include <Servo.h>  

Servo myservo;      //create servo object to control servo

int Echo = 12;  //Echo pin of ultrasonic sensor
int Trig = 13;  //Trig pin of ultrasonic sensor

int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(){ 
digitalWrite(7,HIGH); //Left motors ON
digitalWrite(8,HIGH); //Right motors ON

analogWrite(5,55); //Set Speed for left motors
analogWrite(6,55); //Set Speed for right motors
Serial.println("forward!"); //Text printed when forward function is in use
}

void back() {
digitalWrite(7,LOW); //Left motors OFF
digitalWrite(8,LOW); //Right motors OFF

analogWrite(5,55); //Set Speed for left motors
analogWrite(6,55); //Set Speed for right motors
Serial.println("back!"); //Text printed when back function is in use
}

void left() {
digitalWrite(7,HIGH); //Left motors ON
digitalWrite(8,LOW); //Right motors OFF

analogWrite(5,55); //Set Speed for left motors
analogWrite(6,55); //Set Speed for right motors
Serial.println("left!"); //Text printed when left function is in use
}

void right() {
digitalWrite(7,LOW); //Left motors OFF
digitalWrite(8,HIGH); //Right motors ON

analogWrite(5,55); //Set Speed for left motors
analogWrite(6,55); //Set Speed for right motors
Serial.println("right!"); //Text printed when right function is in use
}

void stop() {
digitalWrite(7,LOW); //Left motors OFF
digitalWrite(8,LOW); //Right motors OFF

analogWrite(5,0); //Set Speed for left motors
analogWrite(6,0); //Set Speed for right motors
Serial.println("stop!"); //Text printed when stop function is in use
} 

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  

void setup() { 
  myservo.attach(10);  // attach servo on pin 10 to servo object
  Serial.begin(9600);  //Initilize serial monitor   
  pinMode(Echo, INPUT); //Pin 12 set as input    
  pinMode(Trig, OUTPUT);  //Pin 13 set as input
  pinMode(5, OUTPUT); //Pin 5 set as an output
  pinMode(6, OUTPUT); //Pin 6 set as an output
  pinMode(7, OUTPUT); //Pin 7 set as an output
  pinMode(8, OUTPUT); //Pin 8 set as an output
  pinMode(3, OUTPUT); //Pin 3 set as an output
  digitalWrite(3,1); //Standby
} 

void loop() { 
    myservo.write(90);  //setservo position according to scaled value
    delay(500); //wait time  
    middleDistance = Distance_test();

    if(middleDistance <= 20) {  //Distance less than 20   
      stop(); //stop
      delay(500);  //wait time                        
      myservo.write(10); //setservo position    
      delay(1000);  //wait time    
      rightDistance = Distance_test();
      
      delay(500); //wait time  
      myservo.write(90);  //setservo position         
      delay(1000); //wait time                                              
      myservo.write(180);              
      delay(1000); //wait time                                              
      leftDistance = Distance_test();
      
      delay(500); //wait time 
      myservo.write(90); //setservo position according to scaled value           
      delay(1000); //wait time                                              
      if(rightDistance > leftDistance) {
        right(); //Use right function
        delay(360); //wait time  
      }
      else if(rightDistance < leftDistance) {
        left(); //Use left function
        delay(360); //wait time  
      }
      else if((rightDistance <= 20) || (leftDistance <= 20)) {
        back(); //Use back function
        delay(180); //wait time  
      }
      else {
        forward(); //Use forward function
      }
    }  
    else {
        forward(); //Use forward function
    }                     
}
