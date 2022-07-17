#include "LoRa_E32.h"
#include <SoftwareSerial.h>
#include "MPU6050.h" //Mpu6050 kütüphanesi
SoftwareSerial mySerial(10, 11); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX
LoRa_E32 e32ttl(&mySerial);
MPU6050 accelgyro; // Mpu6050 sensör tanımlama

int xx;
int yy;
int zz;


typedef  struct {
  int x;
  int y;
  int z;
} Signal;

Signal data;



void setup() {
  Serial.begin(9600);
  e32ttl.begin();
  Wire.begin();
accelgyro.initialize();

}

void loop() {
  while (e32ttl.available()  > 1) {
    ResponseStructContainer rsc = e32ttl.receiveMessage(sizeof(Signal));
    data =*(Signal*) rsc.data;
    rsc.close();
//   int16_t x=int16_t(data.xx);
//   int16_t y=int16_t(data.yy);
//   int16_t z=int16_t(data.zz);
  xx = map(data.x,-17000,17000,0,180);
  yy = map(data.y,-17000,17000,0,180);
  zz= map(data.z,-17000,17000,0,180);
    Serial.print(F(" x: "));
    Serial.print("  ");
    Serial.print(F(" y: "));
    Serial.print("  ");
    Serial.println(F(" z: "));
    Serial.print("  ");
    Serial.print(data.x);
Serial.print("  ");
    Serial.print(data.y);
    Serial.print("  ");
     Serial.println(data.z);
  }

}
