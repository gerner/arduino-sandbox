#include "Wire.h"

#define MAX_LEN 255
int len = 0;
char buf[MAX_LEN];

void setup() {
    Serial.begin(38400);
    Serial.println("I am the peripheral");
    Wire.begin(0x11);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop() {
}

void receiveEvent(int howMany)
{
    Serial.println("receiving");
    while(0 < Wire.available()) {
        // ignore bytes after max length
        if(len >= MAX_LEN) {
            continue;
        }
        buf[len] = Wire.read();
        len++;
    }
    Serial.print("buffer length ");
    Serial.println(len);
}

void requestEvent() {
    Serial.println("echoing back");
    Wire.write(buf, len);
    Serial.print("echo length ");
    Serial.println(len);
    len = 0;
}
