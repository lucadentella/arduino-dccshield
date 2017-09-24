#include <NmraDcc.h>

#define RED_PIN   5
#define GREEN_PIN 6
#define ADDRESS   10

int redValue = 0;
int greenValue = 0;
int actualDirection = 0;
int actualSpeed = 0;
int actualLed = 0;

NmraDcc Dcc;

void notifyDccSpeed( uint16_t Addr, DCC_ADDR_TYPE AddrType, uint8_t Speed, DCC_DIRECTION Dir, DCC_SPEED_STEPS SpeedSteps ) {

  if(Addr == ADDRESS) {

    if(actualDirection != Dir) {

      Serial.print("Changed direction: ");
      Serial.println(Dir);
      
      if(Dir == 0) {
        analogWrite(RED_PIN, 0);
        actualDirection = 0;
        actualLed = GREEN_PIN;
      } else {
        analogWrite(GREEN_PIN, 0);
        actualDirection = 1;
        actualLed = RED_PIN;
      }
    }

    if(actualSpeed != Speed) {

      Serial.print("Changed speed: ");
      Serial.println(Speed);
      
      analogWrite(actualLed,Speed * 2);
      actualSpeed = Speed;
    }
  }
}

void setup()
{
  
  Serial.begin(115200);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  Dcc.pin(0, 2, 1);
  Dcc.init(MAN_ID_DIY, 10, 0, 0);

  Serial.println("Led throttle ready!");
}

void loop()
{

  Dcc.process();
}
