bool pinStatus = HIGH;
void setup() {

  for (int i = 0; i < 20; i++) {
    pinMode(i, OUTPUT);
  }

}

void loop() {
  for (int i = 0; i < 20; i++) {
    digitalWrite(i, pinStatus);
  }
  pinStatus = !pinStatus;
  delay(1000);
}
