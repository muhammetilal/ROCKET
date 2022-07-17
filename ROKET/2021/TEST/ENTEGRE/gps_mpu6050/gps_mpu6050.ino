#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
SoftwareSerial serial_connection(3,4); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;


long val, val2;
long prevVal;


void setup()
{
      Wire.begin();
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
      mpu.initialize();
  serial_connection.begin(9600);//This opens up communications to the GPS
 // Serial.println("GPS Start");//Just show to the monitor that the sketch has started
}

void loop()
{
  
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    //Serial.println("Satellite Count:");
    //Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude:");
    Serial.println(gps.location.lng(), 6);
 //   Serial.println("Speed MPH:");
   // Serial.println(gps.speed.mph());
   // Serial.println("Altitude Feet:");
   // Serial.println(gps.altitude.feet());
   // Serial.println("");
          mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    val = map(ay, -17000, 17000, 0, 180);
    val2 = map(ax, -17000, 17000, 0, 180);
      Serial.print("Gyro X = ");
  Serial.println(val2);
//Serial.print("\t");
  Serial.print("Gyro Y = ");

    Serial.println(val);
        delay(100);
  }
}
