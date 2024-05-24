#include <Wire.h>
#include <MPU6050.h>
#include <ESP32Servo.h>

MPU6050 mpu;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ;
int val1;int val2;

void setup() {
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
  
  
  servo1.attach(4);
  servo2.attach(18);
  servo3.attach(5);
  servo4.attach(19);  // Attach the servo on pin 18 to the servo object
  Serial.begin(115200);
}

void loop() {
  mpu.getAcceleration(&AcX, &AcY, &AcZ);
  
  // Map the raw accelerometer value (AcX) to a range of 0 to 180 for the servo
  val1 = map(AcX, -17000, 17000, 0, 180); val2 = map(AcX, -17000, 17000, 180, 0);
  
  // Constrain the mapped value to ensure it's within the valid range
  val1 = constrain(val1, 0, 180); val2 = constrain(val2, 0, 180);
  
   //Write the value to the servo
   servo1.write(val2);
   servo2.write(val2);
   servo3.write(val1);
   servo4.write(val1);
  
  // Print the values for debugging
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | Mapped Value = "); Serial.print(val1);Serial.println(val2);
  
  delay(100);  // Delay for stability
}
