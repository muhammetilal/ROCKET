#include <Wire.h>
#include <Adafruit_BMP085.h>
 
Adafruit_BMP085 bmp;
   
void setup() {

  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Sensör Bulunamadı!");
    while (1) {}
  }
    Serial.print("Basinc  ");
      Serial.print("Rakim  "); 
      Serial.print("Gercek_Rakim  ");
      Serial.println("Yukseklik  ");
}

void loop() {

     
    //Serial.print("Basinc  ");
    Serial.print(bmp.readPressure());
//    Serial.println(" Pa");
   Serial.print("  ");
    //Serial.print("Rakim  ");
    Serial.print(bmp.readAltitude());
  //  Serial.println(" metre");
 
 Serial.print("    ");

  //  Serial.print("Gercek_Rakim  ");
    Serial.print(bmp.readAltitude(101500));
    //Serial.println(" metre");
 Serial.print("      ");
    //Serial.print("Yukseklik  ");
    Serial.print(bmp.readAltitude(101500)-bmp.readAltitude());
    //Serial.println(" metre");
     
    Serial.println();
    delay(100);



      
}
