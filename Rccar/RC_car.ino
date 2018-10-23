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
  }
  else
    Serial.println("connection failed");
}
  
  

char c;
void loop()
{
    if (client.available())
  {
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
         }else
             Serial.println("connection failed");

  }
  
}

