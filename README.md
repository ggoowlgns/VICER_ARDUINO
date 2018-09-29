# VICER Arduino

## 소개
클라이언트가 차량을 제어할 때 사용할 컨트롤러와 차량의 모형이 되는 RC카의 제어를 위한 Arduino Code이다.

#### 기능
* 컨트롤러 : 핸들, 기어, 엑셀을 통하여 RC카의 움직임을 제어한다.
* RC 카 : Sensing 한 데이터를 서버로부터 전송받아 동작한다.

## 설치 방법 및 실행 환경
Arduino 자체의 통신 기능이 없기 때문에 RC카에는 와이파이 shield 모듈을 추가하여 TCP/IP 소켓 통신을 무선 인터넷 환경에 접속 하였다. </br>
컨트롤러에서는 Bluetooth 모듈을 사용하여 클라이언트의 Application과 p2p 통신을 진행하였다. </br>

### Arduino 
* 본 디바이스는 아두이노 R3버전을 사용합니다.
  * 다른 버전의 아두이노 보드를 사용해도 무방하나, 우노와는 다르게 선으로 와이파이 쉴드를 연결 해 주어야 합니다.
* [아두이노 IDE 설치](https://www.arduino.cc/en/Main/Software)
  * 아두이노 보드에 코드를 업로드 하기 위해 위의 링크에서 에디터를 다운받습니다.      

#### 컨트롤러 
<img src="./Img_ino/컨트롤러 회로도.jpg">

```
아두이노에 연결시킬 포트번호
SoftwareSerial BTSerial(2, 3); // 2 : TX, 3 : RX
int gear = analogRead(A0);
int steer = analogRead(A1);
int accel = analogRead(A2);
```
본 디바이스의 아두이노를 위의 회로도대로 연결 시킨 뒤 깃에 함께 commit된 코드를 업로드한다.
* 완성된 컨트롤러의 모습
<img src="./Img_ino/핸들.jpg">
</br>
#### RC 카
<img src="./Img_ino/RC카 회로도.jpg">
* 아두이노 보드와 추가 모듈들(모터제어 모듈, 와이파이 쉴드 모듈)을 수직으로 붙여 RC카에 연결한다. </br>
* 배터리와 360도 카메라도 RC카 위에 함께 장착한다.

* 완성된 RC카의 모습
<img src="./Img_ino/RC카.jpg">
</br>





1. 소개
2. 설치 및 환경 잡는법
3. 실행방법
4. 실행 결괴
실드 코드
https://www.arduino.cc/en/Guide/ArduinoWiFiShield
