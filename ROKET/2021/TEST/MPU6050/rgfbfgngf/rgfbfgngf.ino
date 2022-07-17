
#include   <MPU6050.h>
#include   <Wire.h> // MPU6050 I2C  KÜTÜPHANESİ
//****************************************************************************************
MPU6050 ACC_GYR;

//16-BITLIK DEGISKEN KULLANDIK. ÇÜNKÜ GELEN DATALAR 16 BİT 
int16_t accx, accy, accz;  
int16_t gyrx, gyry, gyrz; 

int deger; 

void setup(){
    Serial.begin(9600); 
    Serial.println("MPU6050 ARDUINO HOCAM");
    Serial.println("http://www.youtube.com/ArduinoHocam/");
    ACC_GYR.initialize(); // 
    Serial.println(ACC_GYR.testConnection() ? "BASARILI":"BASARISIZ"); // EĞER BAĞALANTI BASARILI ISE mpu.testConnection()=1 OLUR 
                  // VE "BASARILI" AKTIF OLUR. DEGILSE "BASARISIZ" AKTIF OLUR
    
                  
}

void loop(){
    ACC_GYR.getMotion6(&accx, &accy, &accz, &gyrx, &gyry ,&gyrz); // HER BIRI 16-BIT OLANA DATALARI ALDIK
    
    deger=map(accx,-17000,17000,0,180);// X EKSENİNDEKİ DATAYI 0-180 ARASINA ÖLÇEKLENDİRDİK
    
   
      Serial.println(deger); //DEĞERLERİ YAZDIRDIK.
   
    
    delay(50);
}
