#include <SPI.h>
#include "RF24.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

int data[2];

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(){
Wire.begin();
mpu.initialize();
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(pipe);
}

void loop(){
mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
data[0] = map(ax, 10, 17000, 2,178);
data[1] = map(ay, 10, 17000, 2,178);
radio.write(data,sizeof(data));
   {

    Serial.println(data[0]);

    Serial.println(data[1]);
    }
 
}
