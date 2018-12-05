#include <SoftwareSerial.h>


SoftwareSerial BTSerial(2, 3); // 2 : TX, 3 : RX


int temp = 570;
bool gearaccel = false;
bool gearreverse = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  
  int gear = analogRead(A0);
  int steer = analogRead(A1);
  int accel = analogRead(A2);
  
  //Serial.println(gear);
  //Serial.println(accel);
  //Serial.println(steer);

  if (gear > 700) {
    gearaccel = true;
    gearreverse = false;
  }
  else if (gear < 640){
    gearaccel = false;
    gearreverse = true;
  }
  else{
    gearaccel = false;
    gearreverse = false;
  }
    // case1: 전진  
  if (gearaccel)
  {
      if (steer - temp < 5 && steer - temp > -5) {
        if (accel >= 425)
        {
          BTSerial.print("S");
        }
        else if (accel < 425)
        {
          BTSerial.print("F");
        }
      }
      else {
        if (accel >= 425)
        {
          String steerstr = String(steer);
          BTSerial.print("{" + steerstr + "}");
        }
        else
        {
          BTSerial.print("G"); //오른쪽앞
        }
    } 
    delay(100);
    temp = steer;
  }
  //case 2 후진
  else if (gearreverse)
  {
      if (steer - temp < 5 && steer - temp > -5) {
        if (accel >= 425)
        {
          BTSerial.print("S");
        }
        else if (accel < 425)
        {
          BTSerial.print("B");
        }
      }
      else {
        if (accel >= 425)
        {
          String steerstr = String(steer);
          BTSerial.print("{" + steerstr + "}");
        }
        else
        {
          BTSerial.print("H"); //오른쪽뒤
        }
      } 
      delay(100);
    temp = steer;
  }
  else if(!gearaccel && !gearreverse){
    String steerstr = String(steer);
    BTSerial.print("{" + steerstr + "}");
    delay(100);
    temp = steer;
  }
}
