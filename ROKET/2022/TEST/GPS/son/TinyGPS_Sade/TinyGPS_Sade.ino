

#include <TinyGPS.h>
TinyGPS gps;
#include <SoftwareSerial.h>
SoftwareSerial ss(10, 11); //rx tx

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
}

void loop() {
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
}


static void smartdelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
