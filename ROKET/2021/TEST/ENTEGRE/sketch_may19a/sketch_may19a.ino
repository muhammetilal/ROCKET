

/*

Connections:

MPU6050_____UNO
VCC_________3.3v
GND_________GND
SCL_________PinA5
SDA_________PinA4

*/












#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

#include <TinyGPS.h>
TinyGPS gps;
#include <SoftwareSerial.h>
SoftwareSerial ss(10, 11); //rx tx

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;


long val, val2;
long prevVal;

void setup() 
{
    Wire.begin();
    Serial.begin(9600);
    mpu.initialize();
      ss.begin(9600); //GPS için
}

void loop() 
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    val = map(ay, -17000, 17000, 0, 180);
    val2 = map(ax, -17000, 17000, 0, 180);
      Serial.print("Gyro X = ");
  Serial.println(val2);
//Serial.print("\t");
  Serial.print("Gyro Y = ");

    Serial.println(val);
    ///////////////////GPS İÇİN
    smartdelay(1000);
  Serial.println();

  uint8_t sat = gps.satellites();
  Serial.print("sat: "); Serial.println(sat);

  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  Serial.print("lat: "); Serial.println(flat, 6);
  Serial.print("lon: "); Serial.println(flon, 6);

  int alt = gps.f_altitude();
  Serial.print("alt: "); Serial.println(alt);

  int spd = gps.f_speed_kmph();
  Serial.print("spd: "); Serial.println(spd);

  int crs = gps.f_course();
  Serial.print("crs: "); Serial.println(crs);

  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age2;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);

  Serial.print("year: "); Serial.println(year);
  Serial.print("month: "); Serial.println(month);
  Serial.print("day: "); Serial.println(day);

  Serial.print("hour: "); Serial.println(hour + 3);
  Serial.print("minute: "); Serial.println(minute);
  Serial.print("second: "); Serial.println(second);

    delay(100);
}
static void smartdelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
