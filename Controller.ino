#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // 2 : TX, 3 : RX

String myString = "";
int temp = 510;
bool a = true;
bool gearaccel = false;
bool gearreverse = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
  
}

void loop() {


  if(a){
    Serial.print("S");
//    BTSerial.print("S");
    a = false;
  }
  // put your main code here, to run repeatedly:
  //  char my;
  //     // BTSerial 하는 부분
  //  while(Serial.available())
  //  {
  //    my=(char)Serial.read();
  //    myString+=my;
  //    delay(10);
  //  }
  //
  // if(!myString.equals(""))
  //  {
  //     BTSerial.print(myString);
  //     myString="";
  //  }


  //
  //if( 0<gear && gear <340)
  //{
  ////case 0:중립
  //
  //
  //}
  int gear = analogRead(A0);
  int steer = analogRead(A1);
  int accel = analogRead(A2);
  //Serial.println(gear);
  Serial.println(accel);
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
  
  if (gearaccel)
  {
    // case1: 전진
    if (steer - temp >= 0)
    {
      if (steer - temp < 5 && steer - temp > -5) {
        if (accel >= 375)
        {
          BTSerial.print("S");
        }
        else if (accel < 375)
        {
          BTSerial.print("F");
        }
      }
      else {
        if (accel >= 375)
        {
          BTSerial.print("L");
        }
        else
        {
          BTSerial.print("G"); //오른쪽앞
        }
      }
      delay(100);
    } else if (steer - temp < 0) {
      if (steer - temp < 5 && steer - temp > -5) {
        if (accel >= 375)
        {
         BTSerial.print("S");
        }
        else if (accel < 375)
        {
          BTSerial.print("F");
        }
      }

      else {
        if (accel >= 375)
        {
          BTSerial.print("R");
        }
        else
        {
          BTSerial.print("I"); //왼쪽앞
        }
      }
      delay(100);
    }
    temp = steer;
  }
  else if (gearreverse)
  {
    //case 2 후진
    if (steer - temp >= 0)
    {
      if (steer - temp < 5 && steer - temp > -5) {
        if (accel >= 375)
        {
          BTSerial.print("S");
        }
        else if (accel < 375)
        {
          BTSerial.print("B");

        }
      }
      else {
        if (accel >= 375)
        {
          BTSerial.print("L");
        }
        else
        {
          BTSerial.print("H"); //오른쪽뒤
        }
      }
      delay(100);
    } else if (steer - temp < 0) {
      if (steer - temp < 5 && steer - temp > -5) {
        if (accel >= 375)
        {
          BTSerial.print("S");
        }
        else if (accel < 375)
        {
          BTSerial.print("B");

        }

      }
      else {
        if (accel >= 375)
        {
          BTSerial.print("R");
        }
        else
        {
          BTSerial.print("J"); //왼쪽뒤
        }
      }
      delay(100);
    }
    temp = steer;
  }
  else if(!gearaccel && !gearreverse){
    if(steer - temp >= 5){
      BTSerial.print("L");
    }
    else if(steer - temp < -5){
      BTSerial.print("R");
    }
    delay(100);
    temp = steer;
  }
}
