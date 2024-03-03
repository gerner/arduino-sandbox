#include <Servo.h>

Servo servo;
int last_value = -1000;

void setup() {
    servo.attach(11);
    Serial.begin(115200);
}

void loop() {
    int value = analogRead(A0);
    int angle = map(value, 0, 1024, 0, 180);
    if(abs(last_value - value) > 2) {
        last_value = value;
        char s[32];
        snprintf(s, sizeof(s), "v: %d\ta: %d", value, angle);
        Serial.println(s);
    }
    servo.write(angle);
}
