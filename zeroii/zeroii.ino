//#include "RigExpertZeroII_UART.h"
/*void setup() {
    Serial.begin(38400);
    Serial.flush();

    Serial.println("setting up");

    pinMode(ZEROII_Reset_Pin, OUTPUT);
    pinMode(RX_PIN, INPUT);
    pinMode(TX_PIN, OUTPUT);

    long bauds[] = {300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200};

    for(int i=0; i<sizeof(bauds)/sizeof(bauds[0]); i++) {
        Serial.print("trying baud ");
        Serial.println(bauds[i]);

        Serial.println("resetting ZEROII");
        digitalWrite(ZEROII_Reset_Pin, LOW);
        delay(500);
        digitalWrite(ZEROII_Reset_Pin, HIGH );

        SoftwareSerial ZERO(RX_PIN, TX_PIN);
        ZERO.begin(bauds[i]);
        ZERO.flush();
        delay(500);

        char command[3] = {0x5A,0x81,0x7E};
        ZERO.write(command,3);
        ZERO.flush();

        Serial.println("waiting...");
        delay(500);
        Serial.print("available: ");
        Serial.println(ZERO.available());
        if(ZERO.available() > 0) {
            Serial.println(bauds[i]);
            break;
        }
    }
}*/

#include "RigExpertZeroII_I2C.h"
#include "Wire.h"

#define ZEROII_Reset_Pin  6
#define ZERO_I2C_ADDRESS 0x5B

RigExpertZeroII_I2C zeroii = RigExpertZeroII_I2C();

void setup() {
    Serial.begin(38400);
    Serial.flush();

    Serial.println("resetting ZEROII");
    pinMode(ZEROII_Reset_Pin, OUTPUT);
    digitalWrite(ZEROII_Reset_Pin, LOW);
    delay(50);
    digitalWrite(ZEROII_Reset_Pin, HIGH);

    if(!zeroii.startZeroII()) {
        Serial.println("failed to start zeroii");
        return;
    }

    String str = "Version: ";
    Serial.println(str + zeroii.getMajorVersion() + "." + zeroii.getMinorVersion() + 
            ", HW Revision: " + zeroii.getHwRevision() + 
            ", SN: " + zeroii.getSerialNumber()
    );

    analyze();

    Serial.println("done");
}

void loop() {
    delay(500);
}

void analyze() {
    double Z0 = 50;
    int32_t centerFq = 300000000;// 148 000 000 Hz
    int32_t rangeFq =  400000000;// 10 000 000 Hz
    int32_t dotsNumber = 200;

    int32_t startFq = centerFq - (rangeFq/2);
    int32_t endFq = centerFq + (rangeFq/2);
    int32_t stepFq = (endFq - startFq)/dotsNumber;

    zeroii.setZ0(50);

    for(int i = 0; i <= dotsNumber; ++i)
    {
        int32_t temp = startFq + (stepFq*i);
        zeroii.startMeasure(temp);
        Serial.print("Fq: ");
        Serial.print(temp);
        Serial.print(", R: ");
        Serial.print(zeroii.getR());
        Serial.print(", Rp: ");
        Serial.print(zeroii.getRp());
        Serial.print(", X: ");
        Serial.print(zeroii.getX());
        Serial.print(", Xp: ");
        Serial.print(zeroii.getXp());
        Serial.print(", SWR: ");
        Serial.print(zeroii.getSWR());
        Serial.print(", RL: ");
        Serial.print(zeroii.getRL());
        Serial.print(", Z: ");
        Serial.print(zeroii.getZ());
        Serial.print(", Phase: ");
        Serial.print(zeroii.getPhase());
        Serial.print(", Rho: ");
        Serial.print(zeroii.getRho());
        Serial.print("\r\n");        
    }
    Serial.print("------------------------\r\n");
}

/*RigExpertZeroII_UART ZERO(RX_PIN, TX_PIN);

  void setup()
  {    
  pinMode(ZEROII_Reset_Pin, OUTPUT);
  digitalWrite(ZEROII_Reset_Pin, LOW);
  Serial.begin(38400);
  Serial.flush();
  digitalWrite(ZEROII_Reset_Pin, HIGH );
  while(!ZERO.startZeroII())
  {     
  Serial.println("ZERO not found!");
  delay(500);
  }
  Serial.println("----------------------------");
  Serial.println("Found RigExpert ZEROII!");
  String str = "Version: ";
  Serial.println(str + ZERO.getMajorVersion() + "." + ZERO.getMinorVersion() + 
  ", HW Revision: " + ZERO.getHwRevision() + 
  ", SN: " + ZERO.getSerialNumber());
  }

  void loop()
  {
  int32_t centerFq = 150000000;// 15 000 000 Hz
  int32_t rangeFq =  300000000;// 30 000 000 Hz
  int32_t dotsNumber = 30;

  int32_t startFq = centerFq - (rangeFq/2);
  int32_t endFq = centerFq + (rangeFq/2);
  int32_t stepFq = (endFq - startFq)/dotsNumber;

  for(int i = 0; i <= dotsNumber; ++i)
  {
  int32_t temp = startFq + (stepFq*i);
  ZERO.startMeasure(temp);
  Serial.print("Fq: ");
  Serial.print(temp);
  Serial.print(", R: ");
  Serial.print(ZERO.getR());
  Serial.print(", Rp: ");
  Serial.print(ZERO.getRp());
  Serial.print(", X: ");
  Serial.print(ZERO.getX());
  Serial.print(", Xp: ");
  Serial.print(ZERO.getXp());
  Serial.print(", SWR: ");
  Serial.print(ZERO.getSWR());
  Serial.print(", RL: ");
  Serial.print(ZERO.getRL());
  Serial.print(", Z: ");
  Serial.print(ZERO.getZ());
  Serial.print(", Phase: ");
  Serial.print(ZERO.getPhase());
  Serial.print(", Rho: ");
  Serial.print(ZERO.getRho());
  Serial.print("\r\n");        
  }
  Serial.print("------------------------\r\n");
  delay(5000);
  }*/
