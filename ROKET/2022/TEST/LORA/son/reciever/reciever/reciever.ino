#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX
LoRa_E32 e32ttl(&mySerial);

int x;
int y;
int z;
typedef  struct {
  byte xx;
  byte yy;
  byte zz;
} Signal;

Signal data;



void setup() {
  Serial.begin(9600);
  e32ttl.begin();

}

void loop() {
  while (e32ttl.available()  > 1) {
    ResponseStructContainer rsc = e32ttl.receiveMessage(sizeof(Signal));
    data =*(Signal*) rsc.data;
    rsc.close();
int x=int(data.xx);
int y=int(data.yy);
int z=int(data.zz);
    Serial.print(F(" x: "));
    Serial.print("  ");
    Serial.print(F(" y: "));
    Serial.print("  ");
    Serial.println(F(" z: "));
    Serial.print("  ");
    Serial.print(x);
Serial.print("  ");
    Serial.print(y);
    Serial.print("  ");
     Serial.println(z);
  }

}
