
#include <SoftwareSerial.h>
#include <Servo.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Phpoc.h>


SoftwareSerial mySerial(10, 11); // RX, TX
Servo myservo;

int inByte;
int inByteSoft;

#define Middle_Cal_Addr 0  //THROTTLE 보정값을 저장하는 위치
int Middle_Cal_Val = 0;
int Middle_Val;

#define DIRA  4
#define PWMA  5
#define FORWARD 1
#define BACKWARD  0

int MotorSpped = 110;

char server_name[] = "52.79.181.10";
PhpocClient client;

//모터 방향, 속도 제어
void go_Motor(int Dir, int Speed)
{
  digitalWrite(DIRA, Dir); //모터의 정역
  analogWrite(PWMA, Speed); //모터의 속도 0~255
}


//삼각형 버튼이 빨간색일때 앞바퀴를 고정한다
void Calibration_Cental(void)
{
  while (1)
  {
    if (mySerial.available())
    {
      inByteSoft = mySerial.read();
      if (inByteSoft == 'L') //왼쪽
      {
        Middle_Val = Middle_Val - 1;
        Serial.print("L:");
        Serial.println(Middle_Val);
        myservo.write(Middle_Val);
      }
      else if (inByteSoft == 'R') //오른쪽
      {
        Middle_Val = Middle_Val + 1;
        Serial.print("R:");
        Serial.println(Middle_Val);
        myservo.write(Middle_Val);
      }
      else if (inByteSoft == 'x') //출구
      {
        Serial.print("SaveEEPROM:");
        Serial.println(Middle_Val);
        EEPROM.write(Middle_Cal_Addr, Middle_Val);
        delay(10);
        break;
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  Middle_Cal_Val = EEPROM.read(Middle_Cal_Addr);

  //EEPROM에 보정값이 저장되지 않았다면 초기값인 90으로 저장한다
  if ((Middle_Cal_Val == 0x00) || (Middle_Cal_Val == 0xFF))
  {
    Middle_Cal_Val = 90;
    EEPROM.write(Middle_Cal_Addr, Middle_Cal_Val);
    delay(10);
  }
  Middle_Val = Middle_Cal_Val;

  myservo.attach(9);
  myservo.write(Middle_Cal_Val);

  Serial.begin(9600);

  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  go_Motor(FORWARD, 0);
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
  if(client.connect(server_name, 5001))
  {
    Serial.println("Connected to server");
    client.print("K");
//  client.println();
  }
  else
    Serial.println("connection failed");
}
  
  
  /*
  Middle_Cal_Val = EEPROM.read(Middle_Cal_Addr);

  //EEPROM에 보정값이 저장되지 않았다면 초기값인 90으로 저장한다
  if ((Middle_Cal_Val == 0x00) || (Middle_Cal_Val == 0xFF))
  {
    Middle_Cal_Val = 90;
    EEPROM.write(Middle_Cal_Addr, Middle_Cal_Val);
    delay(10);
  }
  Middle_Val = Middle_Cal_Val;

  myservo.attach(9);
  myservo.write(Middle_Cal_Val);

  mySerial.begin(9600);
  Serial.begin(9600);

  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  go_Motor(FORWARD, 0);
*/

char c;
void loop()
{
    if (client.available())
  {
    //Serial.println("In");
    c = client.read();
    Serial.println(c);
    /*********************************
     * ***********RC CONTROL**********
    ***********************************/
    inByteSoft = c;
    if (inByteSoft == 'S') //모터 스탑
    {
      go_Motor(FORWARD, 0);
    }
    else if (inByteSoft == 'F') //전진
    {
      go_Motor(FORWARD, MotorSpped);
    }
    else if (inByteSoft == 'B') //후진
    {
      go_Motor(BACKWARD, MotorSpped);
    }
    else if (inByteSoft == 'L') //왼쪽
    {
      Serial.println("left");
      if ((Middle_Cal_Val - 30) <= Middle_Val) Middle_Val = Middle_Val - 3;
      myservo.write(Middle_Val);
    }
    else if (inByteSoft == 'R') //오른쪽
    {
      Serial.println("right");
      if ((Middle_Cal_Val + 30) >= Middle_Val) Middle_Val = Middle_Val + 3;
      myservo.write(Middle_Val);
    }
    else if (inByteSoft == 'G') //앞 왼쪽
    {
      go_Motor(FORWARD, MotorSpped);
      if ((Middle_Cal_Val - 30) <= Middle_Val) Middle_Val = Middle_Val - 3;
      myservo.write(Middle_Val);
    }
    else if (inByteSoft == 'I') //앞 오른쪽
    {
      go_Motor(FORWARD, MotorSpped);
      if ((Middle_Cal_Val + 30) >= Middle_Val) Middle_Val = Middle_Val + 3;
      myservo.write(Middle_Val);
    }
    else if (inByteSoft == 'H') //뒤 왼쪽
    {
      go_Motor(BACKWARD, MotorSpped);
      if ((Middle_Cal_Val - 30) <= Middle_Val) Middle_Val = Middle_Val - 3;
      myservo.write(Middle_Val);
    }
    else if (inByteSoft == 'J') //뒤 오른쪽
    {
      go_Motor(BACKWARD, MotorSpped);
      if ((Middle_Cal_Val + 30) >= Middle_Val) Middle_Val = Middle_Val + 3;
      myservo.write(Middle_Val);
    }
    else if (inByteSoft == 'X') //삼각형 버튼, 중간보정
    {
      Calibration_Cental();

    }
    else if (inByteSoft == '0') //모터속도 0
    {
      Serial.println("Speed=0");
      MotorSpped = 150;
    }
    else if (inByteSoft == '1') //모터속도 1
    {
      Serial.println("Speed=1");
      MotorSpped = 160;
    }
    else if (inByteSoft == '2') //모터속도 2
    {
      Serial.println("Speed=2");
      MotorSpped = 170;
    }
    else if (inByteSoft == '3') //모터속도 3
    {
      Serial.println("Speed=3");
      MotorSpped = 180;
    }
    else if (inByteSoft == '4') //모터속도 4
    {
      Serial.println("Speed=4");
      MotorSpped = 190;
    }
    else if (inByteSoft == '5') //모터속도 5
    {
      Serial.println("Speed=5");
      MotorSpped = 200;
    }
    else if (inByteSoft == '6') //모터속도 6
    {
      Serial.println("Speed=6");
      MotorSpped = 210;
    }
    else if (inByteSoft == '7') //모터속도 7
    {
      Serial.println("Speed=7");
      MotorSpped = 220;
    }
    else if (inByteSoft == '8') //모터속도 8
    {
      Serial.println("Speed=8");
      MotorSpped = 230;
    }
    else if (inByteSoft == '9') //모터속도 9
    {
      Serial.println("Speed=9");
      MotorSpped = 240;
    }
    else if (inByteSoft == 'q') //모터속도 MAX
    {
      Serial.println("Speed=q");
      MotorSpped = 255;
    }
   delay(10);
  }

  else
  {
    Serial.println("get noting from server");
    delay(10);
  }

   



  if (!client.connected())
  {
   
    Serial.println("disconnected");
    client.stop();
                
        if (client.connect(server_name, 5001))
        {
             Serial.println("Connected to server");
             client.print("K");
//             client.println();
         }else
             Serial.println("connection failed");

  }
   
  
  /*
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if (inByte == '1')
    {
      Middle_Val = Middle_Val + 5;
      Serial.println(Middle_Val);
      myservo.write(Middle_Val);
    }
    else if (inByte == '2')
    {
      Middle_Val = Middle_Val - 5;
      Serial.println(Middle_Val);
      myservo.write(Middle_Val);
    }
    else if (inByte == '3')
    {
      Middle_Val = Middle_Val + 1;
      Serial.println(Middle_Val);
      myservo.write(Middle_Val);
    }
    else if (inByte == '4')
    {
      Middle_Val = Middle_Val - 1;
      Serial.println(Middle_Val);
      myservo.write(Middle_Val);
    }
    else if (inByte == '0')
    {
      Serial.print("SaveEEPROM:");
      Serial.println(Middle_Val);
      EEPROM.write(Middle_Cal_Addr, Middle_Val);
      delay(10);
    }
  }
*/
  
}

