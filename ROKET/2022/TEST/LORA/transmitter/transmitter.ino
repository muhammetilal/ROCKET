#include "I2Cdev.h" //I2C kütüphanesi
#include "MPU6050.h" //Mpu6050 kütüphanesi
#include "Wire.h"
#include <Adafruit_BMP085.h>
#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);

/*
   Pinler     Arduino Nano    Lora E32 433T20d
                  11                3
                  10                4
*/


#include <TinyGPS.h>
TinyGPS gps;
#include <SoftwareSerial.h>
SoftwareSerial ss(4,3); //rx tx
MPU6050 accelgyro; // Mpu6050 sensör tanımlama
Adafruit_BMP085 bmp; //BMP
int16_t ax, ay, az; //ivme tanımlama
int16_t gx, gy, gz; //gyro tanımlama


LoRa_E32 e32ttl(&mySerial);

typedef  struct {
  byte bas;
  byte yuk;
  byte xeksen;
  byte yeksen;
  byte zeksen;
  byte enlem;
  byte boylam;

} Signal;

Signal data;


  
void setup() {
Wire.begin();
 Serial.begin(9600);
  ss.begin(9600);
  e32ttl.begin();
Serial.println("I2C cihazlar başlatılıyor...");
accelgyro.initialize();
Serial.println("Test cihazı bağlantıları...");
Serial.println(accelgyro.testConnection() ? "MPU6050 bağlantı başarılı" : "MPU6050 bağlantısı başarısız");
  if (!bmp.begin()) {
    Serial.println("Sensör Bulunamadı!");
    while (1) {}
  }
}
  
void loop() {
    smartdelay(100);
accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // ivme ve gyro değerlerini okuma
  
//açısal ivmeleri ve gyro değerlerini ekrana yazdırma
//Serial.print("a/g:\t");
Serial.print(ax); Serial.print("      ");
Serial.print(ay); Serial.print("      ");
Serial.print(az); Serial.print("      ");
Serial.print(gx); Serial.print("      ");
Serial.print(gy); Serial.print("       ");
Serial.print(gz); Serial.print("       ");


    //Serial.print("Basinc  ");
  //  Serial.print(bmp.readPressure());//Serial.print("\t");


//    Serial.println(" Pa");
//   Serial.print("  ");

//    Serial.print(bmp.readAltitude(101500)-bmp.readAltitude());//Serial.print("\t");





      uint8_t sat = gps.satellites();
 // Serial.print("sat: "); Serial.println(sat);

  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  //Serial.print("lat: ");
  //Serial.print("      ");
  //Serial.print(flat, 6);
 // Serial.print("      ");
 // Serial.print("lon: "); 
 // Serial.println(flon, 6);

  int alt = gps.f_altitude();
  //Serial.print("alt: "); Serial.println(alt);

  int spd = gps.f_speed_kmph();
  //Serial.print("spd: "); Serial.println(spd);

  int crs = gps.f_course();
//  Serial.print("crs: "); Serial.println(crs);

  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age2;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);

    //parametreler
    data.bas=bmp.readPressure();

  data.yuk = (bmp.readAltitude(101500)-bmp.readAltitude());
  data.xeksen = gx;
  data.yeksen = gy;
  data.zeksen = gz;
  data.enlem = (flat, 6);
  data.boylam = (flon, 6);

  ResponseStatus rs = e32ttl.sendFixedMessage(0, 2, 4, &data, sizeof(Signal));
  Serial.println( data.bas);



}
static void smartdelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
