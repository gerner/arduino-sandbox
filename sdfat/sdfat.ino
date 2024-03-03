#include <SdFat.h>

SdFat sd;
void setup() {
    Serial.begin(38400);
    Serial.flush();


    //wait for serial data
    char c;
    while(((c = Serial.read()) == 0) || (c != '\n')) {
    }

    if(!sd.begin(10)) {
        Serial.println("could not begin sd");
    } else {
        Serial.println("sd began");
    }

}

void loop() {
}
