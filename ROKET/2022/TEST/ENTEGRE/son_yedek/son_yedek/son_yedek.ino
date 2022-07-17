#include "I2Cdev.h" //I2C kütüphanesi
#include "MPU6050.h" //Mpu6050 kütüphanesi
#include "Wire.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

#include <TinyGPS.h>
TinyGPS gps;
#include <SoftwareSerial.h>
SoftwareSerial ss(4,3); //rx tx
MPU6050 accelgyro; // Mpu6050 sensör tanımlama
int16_t ax, ay, az; //ivme tanımlama
int16_t gx, gy, gz; //gyro tanımlama

int degerx;
int degery;
int degerz;

void setup() {
Wire.begin();
 Serial.begin(9600);
  ss.begin(9600);
  Serial.println(F("BMP280 test"));
accelgyro.initialize();
Serial.print("gyro x  ");
Serial.print("  gyro y  ");
Serial.print("  gyro z  ");
Serial.print("      basınç  ");
Serial.print("         rakım  ");
Serial.print("        enlem  ");
Serial.print("         boylam  ");
Serial.println("       yükseklik ");
  if (!bmp.begin(0x76)) {
    Serial.println("Sensör Bulunamadı!");
    while (1) {}
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
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
Serial.print(degerx); Serial.print("        ");
Serial.print(degery); Serial.print("         ");
Serial.print(degerz); Serial.print("         ");



//    Serial.print(F("Temperature = "));
//    Serial.print(bmp.readTemperature());
//    Serial.println(" *C");

    Serial.print(bmp.readPressure());
     Serial.print("         ");

   

//    Serial.print(F("Approx altitude = "));
//    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
//    Serial.println(" m");
 
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
 // Serial.print("         ");
  Serial.print(flat, 6);
  Serial.print("          ");
 // Serial.print("lon: "); 
  Serial.print(flon, 6);
Serial.print("         ");
  int alt = gps.f_altitude();
   Serial.println(alt);
 //  Serial.println(bmp.readAltitude(101500)-bmp.readAltitude());

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
