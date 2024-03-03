#include <SPI.h>
#include <SD.h>

void print_directory(File dir, int numTabs=0) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      print_directory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void setup() {
    Serial.begin(38400);
    Serial.flush();


    //wait for serial data
    char c;
    while(((c = Serial.read()) == 0) || (c != '\n')) {
    }

    pinMode(A2, INPUT_PULLUP);
    if (digitalRead(A2) == LOW) {
        Serial.println("no card detected!");
        return;
    } else {
        Serial.println("card detected!");
    }

    Sd2Card card;

    /*if(!card.init(SPI_HALF_SPEED, 10)) {
        Serial.println("could not init Sd2Card!");
    } else {
        Serial.println("Sd2Card initialized.");
    }*/
    if(!SD.begin()) {
        Serial.println("could not begin SD!");
    }

    File root = SD.open("/");
    if (!root) {
        Serial.println("could not open root!");
    } else {
        print_directory(root);
    }

    File settings_file = SD.open("settings.json");
    if (!settings_file) {
        Serial.println("could not open settings.json");
    }

    settings_file = SD.open("SETTIN~1.JSO");
    if (!settings_file) {
        Serial.println("could not open SETTIN~1.JSO");
    } else {
        while(settings_file.available()) {
            Serial.write(settings_file.read());
        }
    }
}

void loop() {
}
