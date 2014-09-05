#include <Adafruit_NECremote.h>
#include <SoftwareSerial.h>

#define PIN_RX       3
#define PIN_TX       4
#define PIN_DD       5
#define PIN_IR       7
#define PIN_LED      13
#define INPUT_UP     5
#define INPUT_LEFT   8
#define INPUT_RIGHT  10
#define INPUT_DOWN   13
#define INPUT_STOP   9
#define INPUT_VACUUM 1
#define INPUT_POWER  6

const boolean IGNORE_SAFETY = true;
SoftwareSerial Roomba(PIN_RX, PIN_TX);
Adafruit_NECremote remote(PIN_IR);
int lastInput = -1;
boolean isOn = false;
boolean isVacuuming = false;

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  Roomba.begin(115200);
  Serial.println("Press \"STOP/MODE\" to start!");
}

void loop()
{
  int input = remote.listen();
  
  if (input >= 0)
  {
    lastInput = input;

    switch(input)
    {
       case (int)INPUT_UP:
         MoveForward();
         break;
       case (int)INPUT_LEFT:
         MoveLeft();
         break;
       case (int)INPUT_RIGHT:
         MoveRight();
         break;
       case (int)INPUT_DOWN:
         MoveBackwards();
         break;
       case (int)INPUT_STOP:
         StopMoving();
         break;
       case (int)INPUT_VACUUM:
         ChangeVacuumState();
         break;
       case (int)INPUT_POWER:
         ChangePowerState();
         break;
    }
  }
  else if (input == -3)
  {
    switch(lastInput)
    {
       case (int)INPUT_UP:
         MoveForward();
         break;
       case (int)INPUT_LEFT:
         MoveLeft();
         break;
       case (int)INPUT_RIGHT:
         MoveRight();
         break;
       case (int)INPUT_DOWN:
         MoveBackwards();
         break;
       case (int)INPUT_STOP:
         StopMoving();
         break;
    }
  }
  else if (input == -2)
  {
    Serial.println("Data error");
  }
}

void MoveForward()
{
  if(isOn)
  {
    Serial.println("Forward!");
    Roomba.write(137); //Drive
    Roomba.write((byte)0x00);
    Roomba.write(0xc8);
    Roomba.write(0x80);
    Roomba.write((byte)0x00);
  }
}

void MoveLeft()
{
  if(isOn)
  {
    Serial.println("Left!");
    Roomba.write(137); //Drive
    Roomba.write((byte)0x00);
    Roomba.write(0xc8);
    Roomba.write((byte)0x00);
    Roomba.write(0x01);
  }
}

void MoveRight()
{
  if(isOn)
  {
    Serial.println("Right!");
    Roomba.write(137); //Drive
    Roomba.write((byte)0x00);
    Roomba.write(0xc8);
    Roomba.write(0xff);
    Roomba.write(0xff);
  }
}

void MoveBackwards()
{
  if(isOn)
  {
    Serial.println("Backwards!");
    Roomba.write(137); //Drive
    Roomba.write(0xff);
    Roomba.write(0x38);
    Roomba.write(0x80);
    Roomba.write((byte)0x00);
  }
}

void StopMoving()
{
  if(isOn)
  {
    Serial.println("Stop!");
    Roomba.write(137); //Drive
    Roomba.write((byte)0x00);
    Roomba.write((byte)0x00);
    Roomba.write((byte)0x00);
    Roomba.write((byte)0x00);
  }
}

void ChangeVacuumState()
{
  if(isOn)
  {
    Roomba.write(138); //Motors

    if(isVacuuming)
    {
      Serial.println("Vacuum STOP!");
      Roomba.write((byte)0x00);
    }
    else
    {
      Serial.println("Vacuum START!");
      Roomba.write((byte)0x07); //Side, vacuum, main
    }

    isVacuuming = !isVacuuming;
  }
}

void ChangePowerState()
{
  if(isOn)
  {
    digitalWrite(PIN_LED, LOW); //POWER DOWN
    Roomba.write(137); //Drive
    Roomba.write((byte)0x00);
    Roomba.write((byte)0x00);
    Roomba.write((byte)0x00);
    Roomba.write((byte)0x00);
    Roomba.write(138); //Motors
    Roomba.write((byte)0x00);
    Roomba.write(133); //Power Down
    Serial.println("Power off");
  }
  else
  {
    Roomba.write(128); //Start ROI
    Serial.println("Power on");
    delay(150);
    Roomba.write(IGNORE_SAFETY ? 132 : 131); //Set ROI Mode
    digitalWrite(PIN_LED, HIGH); //Ready for action!   
  }

  isOn = !isOn;
}
