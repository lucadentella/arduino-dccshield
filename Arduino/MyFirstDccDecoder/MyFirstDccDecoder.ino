#include <NmraDcc.h>

#define DCC_PIN 2
#define RED_LED 4
#define GREEN_LED 5

NmraDcc Dcc;

void notifyDccAccTurnoutOutput(uint16_t Addr, uint8_t Direction, uint8_t OutputPower) {

  if(Addr == 4) {
    if(Direction == 0) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);    
    }
  }
    
  Serial.print("Addr: "); Serial.println(Addr);
  Serial.print("Direction: "); Serial.println(Direction);
  Serial.print("OutputPower: "); Serial.println(OutputPower);
  Serial.println("--------------------");
}

void setup() {

  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT); 
  Dcc.pin(digitalPinToInterrupt(DCC_PIN), DCC_PIN, false);
  Dcc.init(MAN_ID_DIY, 1, FLAGS_DCC_ACCESSORY_DECODER | FLAGS_OUTPUT_ADDRESS_MODE, 0);
}

void loop() {

  Dcc.process();
}
