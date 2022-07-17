

#include <SPI.h>
#include <RF24.h>

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int data[2];

void setup()
{
Serial.begin(9600);

radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();
}

void loop()
{
if (radio.available()){
bool done = false;
while (!done){
done = radio.read(data, sizeof(data));

}
  {

    Serial.println(data[0]);

    Serial.println(data[1]);
    }
  }
}
