
#define CLK 2
#define DT 3
#define SW 5
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;

void setup() {
    Serial.begin(9600);  // Setup Serial Monitor
    pinMode(CLK, INPUT);   // Set encoder pins as inputs
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP);
    lastStateCLK = digitalRead(CLK);  // Read the initial state of CLK
}

void loop() {
    currentStateCLK = digitalRead(CLK);  // Read the current state of CLK
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
        if (digitalRead(DT) != currentStateCLK) {
            counter --;
            currentDir = "CCW";
        } else {
            counter ++;
            currentDir = "CW";
        }
        Serial.print("Direction: ");
        Serial.print(currentDir);
        Serial.print(" | Counter: ");
        Serial.println(counter);
    }
    lastStateCLK = currentStateCLK;
    int btnState = digitalRead(SW);
    if (btnState == LOW) {
        if (millis() - lastButtonPress > 50) {
            Serial.println("Button pressed!");
        }
        lastButtonPress = millis();
    }
    delay(1);
}
