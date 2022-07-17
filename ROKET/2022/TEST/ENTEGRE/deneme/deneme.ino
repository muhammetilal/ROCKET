#include "I2Cdev.h" //I2C kütüphanesi
#include "MPU6050.h" //Mpu6050 kütüphanesi
#include "Wire.h"
#include <Adafruit_BMP085.h>
MPU6050 accelgyro; // Mpu6050 sensör tanımlama
Adafruit_BMP085 bmp; //BMP
int16_t ax, ay, az; //ivme tanımlama
int16_t gx, gy, gz; //gyro tanımlama
  
void setup() {
Wire.begin();
Serial.begin(9600);
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
    Serial.print(bmp.readPressure());//Serial.print("\t");
//    Serial.println(" Pa");
   Serial.print("  ");
    //Serial.print("Rakim  ");
   // Serial.print(bmp.readAltitude());Serial.print("\t");
  //  Serial.println(" metre");
 
// Serial.print("    ");

  //  Serial.print("Gercek_Rakim  ");
    //Serial.print(bmp.readAltitude(101500));Serial.print("\t");
    //Serial.println(" metre");
 //Serial.print("      ");
    //Serial.print("Yukseklik  ");
    Serial.print(bmp.readAltitude(101500)-bmp.readAltitude());//Serial.print("\t");
    //Serial.println(" metre");
     
    Serial.println();
     delay(100);

}
