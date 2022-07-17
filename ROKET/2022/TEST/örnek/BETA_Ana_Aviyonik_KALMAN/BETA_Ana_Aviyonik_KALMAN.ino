///GPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(2, 3); //rx ve tx
//////

///XBEE
SoftwareSerial xbee(4,5); //rx ve tx
////////

///YEDEK SİSTEMLE İLETİŞİM
SoftwareSerial yedek_iletisim(6,7); //rx ve tx
#define ana_aktif 8 //digital
//////////////////////////

///MPL3115A2
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
////////////

///MPU9255
#include <MPU9255.h>

#define g 9.81 // 1g ~ 9.81 m/s^2
#define magnetometer_cal 0.06 //magnetometer calibration

MPU9255 mpu;

double process_acceleration(int input, scales sensor_scale )
{
  /*
  To get acceleration in 'g', each reading has to be divided by :
   -> 16384 for +- 2g scale (default scale)
   -> 8192  for +- 4g scale
   -> 4096  for +- 8g scale
   -> 2048  for +- 16g scale
  */
  double output = 1;

  //for +- 2g

  if(sensor_scale == scale_2g)
  {
    output = input;
    output = output/16384;
    output = output*g;
  }

  //for +- 4g
  if(sensor_scale == scale_4g)
  {
    output = input;
    output = output/8192;
    output = output*g;
  }

  //for +- 8g
  if(sensor_scale == scale_8g)
  {
    output = input;
    output = output/4096;
    output = output*g;
  }

  //for +-16g
  if(sensor_scale == scale_16g)
  {
    output = input;
    output = output/2048;
    output = output*g;
  }

  return output;
}

//process raw gyroscope data
//input = raw reading from the sensor, sensor_scale = selected sensor scale
//returns : angular velocity in degrees per second
double process_angular_velocity(int16_t input, scales sensor_scale )
{
  /*
  To get rotation velocity in dps (degrees per second), each reading has to be divided by :
   -> 131   for +- 250  dps scale (default value)
   -> 65.5  for +- 500  dps scale
   -> 32.8  for +- 1000 dps scale
   -> 16.4  for +- 2000 dps scale
  */

  //for +- 250 dps
  if(sensor_scale == scale_250dps)
  {
    return input/131;
  }

  //for +- 500 dps
  if(sensor_scale == scale_500dps)
  {
    return input/65.5;
  }

  //for +- 1000 dps
  if(sensor_scale == scale_1000dps)
  {
    return input/32.8;
  }

  //for +- 2000 dps
  if(sensor_scale == scale_2000dps)
  {
    return input/16.4;
  }

  return 0;
}

//process raw magnetometer data
//input = raw reading from the sensor, sensitivity =
//returns : magnetic flux density in μT (in micro Teslas)
double process_magnetic_flux(int16_t input, double sensitivity)
{
  /*
  To get magnetic flux density in μT, each reading has to be multiplied by sensitivity
  (Constant value different for each axis, stored in ROM), then multiplied by some number (calibration)
  and then divided by 0.6 .
  (Faced North each axis should output around 31 µT without any metal / walls around
  Note : This manetometer has really low initial calibration tolerance : +- 500 LSB !!!
  Scale of the magnetometer is fixed -> +- 4800 μT.
  */
  return (input*magnetometer_cal*sensitivity)/0.6;
}
//////////

///RÖLE
#define suruklenme_role 11
#define ana_role  12
///////

#define buzzer 9

#define delay_sure 50
int ilk_sure = 0, sure = 0;
int ilk_gaz_degeri = 0, gaz_degeri = 0;

bool harekete_gecti_mi = false;
bool ivme_okey_mi = false, donme_okey_mi = false, yukseklik_okey_mi = false;
bool suruklenme_acildi_mi = false, ana_acildi_mi = false;
bool ana_parasut_hazir_mi = false;
bool suruklenme_gorev_tamam_mi = false, ana_gorev_tamam_mi = false;

///KALMAN GENEL TANIMLAR
float kalman_new = 0, cov_new = 0, kalman_gain = 0, kalman_calculated = 0;
int sayac = 0;
////////////////////////

///KALMAN FİLTER İVME
float Xivme_kalman_old = 0 , Xivme_cov_old = 0, Yivme_kalman_old = 0 , Yivme_cov_old = 0, Zivme_kalman_old = 0 , Zivme_cov_old = 0;
float ivmeX = 0, ivmeY = 0, ivmeZ = 0;
//////////////////////

///KALMAN FİLTER DÖNME
float Xdonme_kalman_old = 0 , Xdonme_cov_old = 0, Ydonme_kalman_old = 0 , Ydonme_cov_old = 0, Zdonme_kalman_old = 0 , Zdonme_cov_old = 0;
float donmeX = 0, donmeY = 0, donmeZ = 0;
//////////////////////

///KALMAN YÜKSEKLİK
float yukseklik_kalman_old = 0 , yukseklik_cov_old = 0;
float ilk_yukseklik = 0, yukseklik = 0, yukseklik_fark_degeri = 0;
int yukseklik_sayac = 0;
//////////////////////

void setup() {

  //Serial.begin(9600);
  gpsSerial.begin(9600);
  xbee.begin(9600);
  yedek_iletisim.begin(9600);
  
  ///MPU9255
  if(mpu.init())
  {
    //Serial.println("MPU9255 BULUNAMADI!");
    yedek_iletisim.print("C");
  }
  else
  {
   //Serial.println("MPU9255 BAŞLATILDI.");
  }
  ////////////

  ///MPL315A2 BASINÇ SENSÖRÜ
  
  if (!baro.begin()) 
  {
    //Serial.println("MPL3115A2 BULUNAMADI!");
    yedek_iletisim.print("C");
    return;
  }
  else
  {
    ilk_yukseklik = baro.getAltitude();
    //Serial.println("MPL3115A2 BAŞLATILDI.");
  }
  ////////////

  pinMode(suruklenme_role,OUTPUT);
  pinMode(ana_role,OUTPUT);
  pinMode(ana_aktif,OUTPUT);

  digitalWrite(suruklenme_role,LOW);
  digitalWrite(ana_role,LOW);
  digitalWrite(ana_aktif,HIGH);

  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,HIGH);
  delay(5000);
  digitalWrite(buzzer,LOW);
}

void loop() {

  if(!harekete_gecti_mi)
  {
    yukseklik_degerleri();

    if(yukseklik > 100)
    {
      harekete_gecti_mi = true;
    }
  }

  if(harekete_gecti_mi)
  {
    if(!suruklenme_gorev_tamam_mi)
    {
      suruklenme_parasutu();
    }

    if(!ana_gorev_tamam_mi)
    {
      ana_parasutu();
    }
  }

  gpsSerial.listen();
  GPS_verileri();
}

void suruklenme_parasutu()
{
  ivme_degerleri();
  
  if(ivmeY > -15)
  {
    ivme_okey_mi = true;
  }

  yukseklik_sayac = yukseklik_sayac + 1;
  
  if(yukseklik_sayac > 5)
  {
    yukseklik_farki();
    
    if(yukseklik_fark_degeri > 25 )
    {
      yukseklik_okey_mi = true;
    }

    yukseklik_sayac = 0;
  }

  donme_verileri();
  
  if( (181 > donmeX && donmeX > 160) || (0 < donmeX && donmeX < 20) )
  {
    donme_okey_mi = true;
  }
  else if( (181 > donmeZ && donmeZ > 160) || (0 < donmeZ && donmeZ < 20) )
  {
    donme_okey_mi = true;
  }

  if(ivme_okey_mi && yukseklik_okey_mi && donme_okey_mi)
  {
    suruklenme_atesle();
  }
}

void suruklenme_atesle()
{
  gaz_degeri = analogRead(A0);
  ilk_gaz_degeri = gaz_degeri;
  
  delay(50);
  digitalWrite(suruklenme_role,HIGH);

  sure = millis();
  ilk_sure = sure;
  
  while(sure - ilk_sure < 3000)
  {
    gaz_degeri = analogRead(A0);
    
    if(gaz_degeri-ilk_gaz_degeri > 50 && sure-ilk_sure > 2000)
    {
      suruklenme_acildi_mi = true;
      break;
    }

    sure = millis();
  }

  if(!suruklenme_acildi_mi)
  {
    ///SURUKLENME PARAŞÜTÜ AÇILAMADI!!!!!!!!!!!!!!!!!!!!!!!!
    yedek_iletisim.print("A");
  }
  
  digitalWrite(suruklenme_role,LOW);

  suruklenme_gorev_tamam_mi = true;
}

void ana_parasutu()
{
  yukseklik_degerleri();
  
  if(yukseklik >800)
  {
    ana_parasut_hazir_mi = true;
  }

  if(ana_parasut_hazir_mi)
  {
    yukseklik_degerleri();
    if(yukseklik<800)
    {
      ana_atesle();
    }
  }
}

void ana_atesle()
{
  gaz_degeri = analogRead(A1);
  ilk_gaz_degeri = gaz_degeri;
  
  delay(50);
  digitalWrite(ana_role,HIGH);

  sure = millis();
  ilk_sure = sure;
  
  while(sure - ilk_sure < 3000)
  {
    gaz_degeri = analogRead(A1);
    
    if(gaz_degeri-ilk_gaz_degeri > 50 && sure-ilk_sure > 2000)
    {
      ana_acildi_mi = true;
      break;
    }
    sure = millis();
  }

  if(!ana_acildi_mi)
  {
    ///ANA PARAŞÜTÜ AÇILAMADI!!!!!!!!!!!!!!!!!!!!!!!!
    yedek_iletisim.print("B");
  }
  
  digitalWrite(ana_role,LOW);

  ana_gorev_tamam_mi = true;
}

void ivme_degerleri()
{
  mpu.read_acc();

  ///İvme Değerleri
  /*
  sayac = 0;
  ivmeX = kalman_filter(process_acceleration(mpu.ax,scale_2g));
  */
  sayac = 1;
  ivmeY = kalman_filter(process_acceleration(mpu.ay,scale_2g));
  /*
  sayac = 2;
  ivmeZ = kalman_filter(process_acceleration(mpu.az,scale_2g));
  */
}

void donme_verileri()
{
  mpu.read_acc();
  
  ///Dönme değerleri
  sayac = 3;
  donmeX = kalman_filter(map(mpu.ax,-16384,16384,0,180));
  /*
  sayac = 4;
  donmeY = kalman_filter(map(mpu.ay,-16384,16384,0,180));
  */  
  sayac = 5;
  donmeZ = kalman_filter(map(mpu.az,-16384,16384,0,180));
}

void yukseklik_degerleri()
{
  yukseklik = baro.getAltitude();
  yukseklik = yukseklik - ilk_yukseklik;
}

void yukseklik_farki()
{
  yukseklik_degerleri();
  yukseklik_fark_degeri = yukseklik;
  
  delay(750);

  yukseklik_degerleri();
  yukseklik_fark_degeri = yukseklik_fark_degeri - yukseklik;
}

void GPS_verileri()
{
  while (gpsSerial.available() > 0)
  {
    if (gps.encode(gpsSerial.read()))
    {
      if (gps.location.isValid())
      {
        xbee.print("A");
        delay(delay_sure);
        xbee.print(gps.location.lat(), 6);
        delay(delay_sure);
        xbee.print("Z");
        delay(delay_sure);
        xbee.print("B");
        delay(delay_sure);
        xbee.print(gps.location.lng(), 6);
        delay(delay_sure);
        xbee.print("Z");
        delay(delay_sure);
        xbee.print("C");
        delay(delay_sure);
        xbee.print(gps.speed.kmph());
        delay(delay_sure);
        xbee.print("Z");
        delay(delay_sure);
      }
    }
  }
}

float kalman_filter (float input)
{
  if(sayac == 0)
  {
    kalman_new = Xivme_kalman_old; // eski değer alınır
    cov_new = Xivme_cov_old + 0.50; //yeni kovaryans değeri belirlenir. Q=0.50 alınmıştır
    kalman_gain = cov_new / (cov_new + 0.9); //kalman kazancı hesaplanır. R=0.9 alınmıştır
    
    kalman_calculated = kalman_new + (kalman_gain * (input - kalman_new)); //kalman değeri hesaplanır
  
    cov_new = (1 - kalman_gain) * Xivme_cov_old; //yeni kovaryans değeri hesaplanır
    Xivme_cov_old = cov_new; //yeni değerler bir sonraki döngüde kullanılmak üzere kaydedilir
  
    Xivme_kalman_old = kalman_calculated;

    return kalman_calculated; //hesaplanan kalman değeri çıktı olarak verilir
  }
  
  else if(sayac == 1)
  {
    kalman_new = Yivme_kalman_old; // eski değer alınır
    cov_new = Yivme_cov_old + 0.50; //yeni kovaryans değeri belirlenir. Q=0.50 alınmıştır
    kalman_gain = cov_new / (cov_new + 0.9); //kalman kazancı hesaplanır. R=0.9 alınmıştır
    
    kalman_calculated = kalman_new + (kalman_gain * (input - kalman_new)); //kalman değeri hesaplanır
  
    cov_new = (1 - kalman_gain) * Yivme_cov_old; //yeni kovaryans değeri hesaplanır
    Yivme_cov_old = cov_new; //yeni değerler bir sonraki döngüde kullanılmak üzere kaydedilir
  
    Yivme_kalman_old = kalman_calculated;

    return kalman_calculated; //hesaplanan kalman değeri çıktı olarak verilir
  }
  
  else if(sayac == 2)
  {
    kalman_new = Zivme_kalman_old; // eski değer alınır
    cov_new = Zivme_cov_old + 0.50; //yeni kovaryans değeri belirlenir. Q=0.50 alınmıştır
    kalman_gain = cov_new / (cov_new + 0.9); //kalman kazancı hesaplanır. R=0.9 alınmıştır
    
    kalman_calculated = kalman_new + (kalman_gain * (input - kalman_new)); //kalman değeri hesaplanır
  
    cov_new = (1 - kalman_gain) * Zivme_cov_old; //yeni kovaryans değeri hesaplanır
    Zivme_cov_old = cov_new; //yeni değerler bir sonraki döngüde kullanılmak üzere kaydedilir
  
    Zivme_kalman_old = kalman_calculated;

    return kalman_calculated; //hesaplanan kalman değeri çıktı olarak verilir
  }
  
  else if(sayac == 3)
  {
    kalman_new = Xdonme_kalman_old; // eski değer alınır
    cov_new = Xdonme_cov_old + 0.50; //yeni kovaryans değeri belirlenir. Q=0.50 alınmıştır
    kalman_gain = cov_new / (cov_new + 0.9); //kalman kazancı hesaplanır. R=0.9 alınmıştır
    
    kalman_calculated = kalman_new + (kalman_gain * (input - kalman_new)); //kalman değeri hesaplanır
  
    cov_new = (1 - kalman_gain) * Xdonme_cov_old; //yeni kovaryans değeri hesaplanır
    Xdonme_cov_old = cov_new; //yeni değerler bir sonraki döngüde kullanılmak üzere kaydedilir
  
    Xdonme_kalman_old = kalman_calculated;

    return kalman_calculated; //hesaplanan kalman değeri çıktı olarak verilir
  }
  
  else if(sayac == 4)
  {
    kalman_new = Ydonme_kalman_old; // eski değer alınır
    cov_new = Ydonme_cov_old + 0.50; //yeni kovaryans değeri belirlenir. Q=0.50 alınmıştır
    kalman_gain = cov_new / (cov_new + 0.9); //kalman kazancı hesaplanır. R=0.9 alınmıştır
    
    kalman_calculated = kalman_new + (kalman_gain * (input - kalman_new)); //kalman değeri hesaplanır
  
    cov_new = (1 - kalman_gain) * Ydonme_cov_old; //yeni kovaryans değeri hesaplanır
    Ydonme_cov_old = cov_new; //yeni değerler bir sonraki döngüde kullanılmak üzere kaydedilir
  
    Ydonme_kalman_old = kalman_calculated;

    return kalman_calculated; //hesaplanan kalman değeri çıktı olarak verilir
  }
  
  else if(sayac == 5)
  {
    kalman_new = Zdonme_kalman_old; // eski değer alınır
    cov_new = Zdonme_cov_old + 0.50; //yeni kovaryans değeri belirlenir. Q=0.50 alınmıştır
    kalman_gain = cov_new / (cov_new + 0.9); //kalman kazancı hesaplanır. R=0.9 alınmıştır
    
    kalman_calculated = kalman_new + (kalman_gain * (input - kalman_new)); //kalman değeri hesaplanır
  
    cov_new = (1 - kalman_gain) * Zdonme_cov_old; //yeni kovaryans değeri hesaplanır
    Zdonme_cov_old = cov_new; //yeni değerler bir sonraki döngüde kullanılmak üzere kaydedilir
  
    Zdonme_kalman_old = kalman_calculated;

    return kalman_calculated; //hesaplanan kalman değeri çıktı olarak verilir
  }
  
  else if(sayac == 6)
  {
    kalman_new = yukseklik_kalman_old; // eski değer alınır
    cov_new = yukseklik_cov_old + 0.50; //yeni kovaryans değeri belirlenir. Q=0.50 alınmıştır
    kalman_gain = cov_new / (cov_new + 0.9); //kalman kazancı hesaplanır. R=0.9 alınmıştır
    
    kalman_calculated = kalman_new + (kalman_gain * (input - kalman_new)); //kalman değeri hesaplanır
  
    cov_new = (1 - kalman_gain) * yukseklik_cov_old; //yeni kovaryans değeri hesaplanır
    yukseklik_cov_old = cov_new; //yeni değerler bir sonraki döngüde kullanılmak üzere kaydedilir
  
    yukseklik_kalman_old = kalman_calculated;

    return kalman_calculated; //hesaplanan kalman değeri çıktı olarak verilir
  }
}
