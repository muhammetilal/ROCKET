#include "I2Cdev.h" //I2C kütüphanesi
#include "MPU6050.h" //Mpu6050 kütüphanesi
#include "Wire.h"
#include <Adafruit_BMP085.h>



#include <TinyGPS.h>
TinyGPS gps;
#include <SoftwareSerial.h>
SoftwareSerial ss(4,3); //rx tx
MPU6050 accelgyro; // Mpu6050 sensör tanımlama
Adafruit_BMP085 bmp; //BMP
int16_t ax, ay, az; //ivme tanımlama
int16_t gx, gy, gz; //gyro tanımlama

int degerx;
int degery;
int degerz;

void setup() {
Wire.begin();
 Serial.begin(9600);
  ss.begin(9600);

accelgyro.initialize();
Serial.print("  gyro x    ");
Serial.print("  gyro y    ");
Serial.print("  gyro z    ");
Serial.print("  basınç    ");
Serial.print("  rakım    ");
Serial.print("  enlem    ");
Serial.print("  boylam    ");
Serial.println("  yükseklik   ");
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
//Serial.print(ax); Serial.print("      ");
//Serial.print(ay); Serial.print("      ");
//Serial.print(az); Serial.print("      ");
  degerx = map(ax,-17000,17000,0,180);
  degery = map(ay,-17000,17000,0,180);
  degerz= map(az,-17000,17000,0,180);
Serial.print(degerx); Serial.print("      ");
Serial.print(degery); Serial.print("       ");
Serial.print(degerz); Serial.print("       ");


    //Serial.print("Basinc  ");
    Serial.print(bmp.readPressure());//Serial.print("\t");
//    Serial.println(" Pa");
   Serial.print("     ");
    //Serial.print("Rakim  ");
    Serial.print(bmp.readAltitude());Serial.print("      ");
  //  Serial.println(" metre");
 
// Serial.print("    ");

  //Serial.print("Gercek_Rakim  ");
  //  Serial.print(bmp.readAltitude(101500));
    //Serial.println(" metre");
 //Serial.print("      ");
    //Serial.print("Yukseklik  ");
    //Serial.print(bmp.readAltitude(101500)-bmp.readAltitude());//Serial.print("\t");
    //Serial.println(" metre");
     
   // Serial.println();




      uint8_t sat = gps.satellites();
 // Serial.print("sat: "); Serial.println(sat);

  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  //Serial.print("lat: ");
 // Serial.print("      ");
  Serial.print(flat, 6);
  Serial.print("      ");
 // Serial.print("lon: "); 
  Serial.print(flon, 6);
Serial.print("    ");
  int alt = gps.f_altitude();
  // Serial.println(alt);
   Serial.println(bmp.readAltitude(101500)-bmp.readAltitude());

  int spd = gps.f_speed_kmph();
  //Serial.print("spd: "); Serial.println(spd);

  int crs = gps.f_course();
//  Serial.print("crs: "); Serial.println(crs);

  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age2;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);

//  Serial.print("year: "); Serial.println(year);
  //Serial.print("month: "); Serial.println(month);
//  Serial.print("day: "); Serial.println(day);

  //Serial.print("hour: "); Serial.println(hour + 3);
  //Serial.print("minute: "); Serial.println(minute);
  //Serial.print("second: "); Serial.println(second);
  //   delay(100);

}
static void smartdelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
