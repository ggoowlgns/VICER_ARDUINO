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
  
  
char buf[20];
char bufIndex = 0;
int steer;
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
    else{
      if (inByteSoft == '}'){
        steer = atoi(buf);
        if (steer > 958 && steer <= 970){
          myservo.write(57);
        }
        else if (steer > 946 && steer <= 958){
          myservo.write(58);
        }
        else if (steer > 934 && steer <= 946){
          myservo.write(59);
        }
        else if (steer > 922 && steer <= 934){
          myservo.write(60);
        }
        else if (steer > 910 && steer <= 922){
          myservo.write(61);
        }
        else if (steer > 898 && steer <= 910){
          myservo.write(62);
        }
        else if (steer > 886 && steer <= 898){
          myservo.write(63);
        }
        else if (steer > 874 && steer <= 886){
          myservo.write(64);
        }
        else if (steer > 862 && steer <= 874){
          myservo.write(65);
        }
        else if (steer > 850 && steer <= 862){
          myservo.write(66);
        }
        else if (steer > 838 && steer <= 850){
          myservo.write(67);
        }
        else if (steer > 826 && steer <= 838){
          myservo.write(68);
        }
        else if (steer > 814 && steer <= 826){
          myservo.write(69);
        }
        else if (steer > 802 && steer <= 814){
          myservo.write(70);
        }
        else if (steer > 790 && steer <= 802){
          myservo.write(71);
        }
        else if (steer > 778 && steer <= 790){
          myservo.write(72);
        }
        else if (steer > 766 && steer <= 778){
          myservo.write(73);
        }
        else if (steer > 754 && steer <= 766){
          myservo.write(74);
        }
        else if (steer > 742 && steer <= 754){
          myservo.write(75);
        }
        else if (steer > 730 && steer <= 742){
          myservo.write(76);
        }
        else if (steer > 718 && steer <= 730){
          myservo.write(77);
        }
        else if (steer > 706 && steer <= 718){
          myservo.write(78);
        }
        else if (steer > 694 && steer <= 706){
          myservo.write(79);
        }
        else if (steer > 682 && steer <= 694){
          myservo.write(80);
        }
        else if (steer > 670 && steer <= 682){
          myservo.write(81);
        }
        else if (steer > 658 && steer <= 670){
          myservo.write(82);
        }
        else if (steer > 646 && steer <= 658){
          myservo.write(83);
        }
        else if (steer > 634 && steer <= 646){
          myservo.write(84);
        }
        else if (steer > 622 && steer <= 634){
          myservo.write(85);
        }
        else if (steer > 610 && steer <= 622){
          myservo.write(86);
        }
        else if (steer > 598 && steer <= 610){
          myservo.write(87);
        }
        else if (steer > 586 && steer <= 598){
          myservo.write(88);
        }
        else if (steer > 574 && steer <= 586){
          myservo.write(89);
        }
        else if (steer > 562 && steer <= 574){
          myservo.write(90);
        }
        else if (steer > 550 && steer <= 562){
          myservo.write(91);
        }
        else if (steer > 538 && steer <= 550){
          myservo.write(92);
        }
        else if (steer > 526 && steer <= 538){
          myservo.write(93);
        }
        else if (steer > 514 && steer <= 526){
          myservo.write(94);
        }
        else if (steer > 502 && steer <= 514){
          myservo.write(95);
        }
        else if (steer > 490 && steer <= 502){
          myservo.write(96);
        }
        else if (steer > 478 && steer <= 490){
          myservo.write(97);
        }
        else if (steer > 466 && steer <= 478){
          myservo.write(98);
        }
        else if (steer > 454 && steer <= 466){
          myservo.write(99);
        }
        else if (steer > 442 && steer <= 454){
          myservo.write(100);
        }
        else if (steer > 430 && steer <= 442){
          myservo.write(101);
        }
        else if (steer > 418 && steer <= 430){
          myservo.write(102);
        }
        else if (steer > 406 && steer <= 418){
          myservo.write(103);
        }
        else if (steer > 394 && steer <= 406){
          myservo.write(104);
        }
        else if (steer > 382 && steer <= 394){
          myservo.write(105);
        }
        else if (steer > 370 && steer <= 382){
          myservo.write(106);
        }
        else if (steer > 358 && steer <= 370){
          myservo.write(107);
        }
        else if (steer > 346 && steer <= 358){
          myservo.write(108);
        }
        else if (steer > 334 && steer <= 346){
          myservo.write(109);
        }
        else if (steer > 322 && steer <= 334){
          myservo.write(110);
        }
        else if (steer > 310 && steer <= 322){
          myservo.write(111);
        }
        else if (steer > 298 && steer <= 310){
          myservo.write(112);
        }
        else if (steer > 286 && steer <= 298){
          myservo.write(113);
        }
        else if (steer > 274 && steer <= 286){
          myservo.write(114);
        }
        else if (steer > 262 && steer <= 274){
          myservo.write(115);
        }
        else if (steer > 250 && steer <= 262){
          myservo.write(116);
        }
        else if (steer > 238 && steer <= 250){
          myservo.write(117);
        }
        else if (steer > 226 && steer <= 238){
          myservo.write(118);
        }
        else if (steer > 214 && steer <= 226){
          myservo.write(119);
        }
        else if (steer > 202 && steer <= 214){
          myservo.write(120);
        }
        else if (steer > 190 && steer <= 202){
          myservo.write(121);
        }
        else if (steer > 178 && steer <= 190){
          myservo.write(122);
        }
        else if (steer > 166 && steer <= 178){
          myservo.write(123);
        }
        for(int a=0;a<21;a++) {
           buf[a] = NULL;
        }
        bufIndex = 0;
      }
      else if (inByteSoft == '{'){
      }
      else{
        buf[bufIndex] = inByteSoft;
        bufIndex++;
      }
    }
//    else if (inByteSoft == 'L') //왼쪽
//    {
//      Serial.println("left");
//      if ((Middle_Cal_Val - 30) <= Middle_Val) Middle_Val = Middle_Val - 3;
//      myservo.write(Middle_Val);
//    }
//    else if (inByteSoft == 'R') //오른쪽
//    {
//      Serial.println("right");
//      if ((Middle_Cal_Val + 30) >= Middle_Val) Middle_Val = Middle_Val + 3;
//      myservo.write(Middle_Val);
//    }
//    else if (inByteSoft == 'G') //앞 왼쪽
//    {
//      go_Motor(FORWARD, MotorSpped);
//      if ((Middle_Cal_Val - 30) <= Middle_Val) Middle_Val = Middle_Val - 3;
//      myservo.write(Middle_Val);
//    }
//    else if (inByteSoft == 'I') //앞 오른쪽
//    {
//      go_Motor(FORWARD, MotorSpped);
//      if ((Middle_Cal_Val + 30) >= Middle_Val) Middle_Val = Middle_Val + 3;
//      myservo.write(Middle_Val);
//    }
//    else if (inByteSoft == 'H') //뒤 왼쪽
//    {
//      go_Motor(BACKWARD, MotorSpped);
//      if ((Middle_Cal_Val - 30) <= Middle_Val) Middle_Val = Middle_Val - 3;
//      myservo.write(Middle_Val);
//    }
//    else if (inByteSoft == 'J') //뒤 오른쪽
//    {
//      go_Motor(BACKWARD, MotorSpped);
//      if ((Middle_Cal_Val + 30) >= Middle_Val) Middle_Val = Middle_Val + 3;
//      myservo.write(Middle_Val);
//    }
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
