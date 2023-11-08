
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

int speed;
int speedN;
// Define pin connections & motor's steps per revolution
const int dirPin = 6;
const int stepPin = 5;

const int dirPin_2 = 10;
const int stepPin_2 = 9;

int steps;

void setup()
{
	Serial.begin(115200);

	// Try to initialize!
	if (!mpu.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (1) {
		  delay(10);
		}
	}
	Serial.println("MPU6050 Found!");

	// set accelerometer range to +-8G
	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

	// set gyro range to +- 500 deg/s
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);

	// set filter bandwidth to 21 Hz
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

	delay(100);


	// Declare pins as Outputs
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
  pinMode(stepPin_2, OUTPUT);
  pinMode(dirPin_2, OUTPUT);

  digitalWrite(stepPin, 0);
  digitalWrite(stepPin_2, 0);

}
void loop()
{

	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

  float rotatY=g.gyro.y;
  float rotatX=g.gyro.x;
  float rotatZ=g.gyro.z;
	// Serial.print("Acceleration X: ");
	// Serial.print(a.acceleration.x);
	// Serial.print(", Y: ");
	// Serial.print(a.acceleration.y);
	// Serial.print(", Z: ");
	// Serial.print(a.acceleration.z);
	// Serial.println(" m/s^2");

	// Serial.print("Rotation X: ");
	// Serial.print(g.gyro.x);
	Serial.print(" Y: ");
	Serial.print(g.gyro.y);
	// Serial.print(", Z: ");
	// Serial.print(g.gyro.z);
	// Serial.println(" rad/s");

	// Serial.print("Temperature: ");
	// Serial.print(temp.temperature);
	// Serial.println(" degC");



	Serial.println("");

  // speed=map(rotatY,0.05,3,0,30);
  // speedN=map(rotatY,(-0.05),(-3),0,30);


steps=(rotatY*(-1))*67;
if(steps>200){
  steps=200;
}if(steps<5){
  steps=5;
}

speed=rotatY*10000;
if(speed>30000){
speed=30000;  
}if(speed<(-30000)){
  speed=-30000;
}


if(speed>0){
  speed=31000-speed;
}
if(speed<0){
  speed=31000-(speed*(-1));
}
if(speed<1000){  // minimum limit 
  speed=1000;
}

Serial.print("Speed : ");
Serial.println(speed);

Serial.print("Steps : ");
Serial.println(steps);

Serial.println("");


if(g.gyro.y>(-0.05) && g.gyro.y<(0.05)){
  digitalWrite(stepPin,LOW);  
}
if(g.gyro.y>0){
  for(int i=0;i<steps;i++){
  digitalWrite(dirPin,HIGH);
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(speed);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(speed);
  }
}  
if(g.gyro.y<0){
for(int i=0;i<steps;i++){
  digitalWrite(dirPin,LOW);
  digitalWrite(stepPin,HIGH);
  delay(speed);
  digitalWrite(stepPin,LOW);
  delay(speed);
  }
}  

delay(300);

}