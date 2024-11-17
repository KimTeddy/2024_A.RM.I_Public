# 2024_A.RM.I_Public
2024 캡스톤디자인 1, 2 졸업작품 2024_A.RM.I의 main 코드입니다.

## 작품 사진
### 1차
<table>
    <tr align=center>
        <th width=35%>전면</th>
        <th width=35%>후면</td>
    </tr>
    <tr>
      <td align=center><img src="https://github.com/user-attachments/assets/e7d2cc7d-b772-42bf-8750-27be98a86a54" width="40%"></td>
      <td align=center><img src="https://github.com/user-attachments/assets/e949ea68-ea32-48f8-984c-f265b4a7c2f6" width="40%"></td>
    </tr>
</table>
<!--
![20240603_095538](https://github.com/user-attachments/assets/e7d2cc7d-b772-42bf-8750-27be98a86a54)
![20240603_095737](https://github.com/user-attachments/assets/e949ea68-ea32-48f8-984c-f265b4a7c2f6)
-->

### 2차
<table>
    <tr align=center>
        <th width=35%>PCB 후면</td>
        <th width=35%>케이스 조립(후면)</td>
        <th width=35%>케이스 조립(전면)</td>
    </tr>
    <tr>
      <td align=center><img src="https://github.com/user-attachments/assets/d342c03b-e8ef-4043-bd37-56ef397f784f" width="100%"></td>
      <td align=center><img src="https://github.com/user-attachments/assets/e03ac7db-3003-4ef3-b040-5c6877dd2d39" width="50%"></td>
      <td align=center><img src="https://github.com/user-attachments/assets/997c9095-b84f-441b-9be1-441c1d06dbd6" width="50%"></td>
    </tr>
</table>
<!--
![20240831_171155](https://github.com/user-attachments/assets/d342c03b-e8ef-4043-bd37-56ef397f784f)
![20241106_170117](https://github.com/user-attachments/assets/e03ac7db-3003-4ef3-b040-5c6877dd2d39)
![20241106_170221](https://github.com/user-attachments/assets/997c9095-b84f-441b-9be1-441c1d06dbd6)
-->

### 3차(추가 예정)
<table>
    <tr align=center>
        <th width=35%>PCB 후면</td>
        <th width=35%>PCB 전면</td>
        <th width=35%>케이스 조립(후면)</td>
        <th width=35%>케이스 조립(전면)</td>
    </tr>
    <tr>
      <td align=center><img src="" width="40%"></td>
      <td align=center><img src="" width="40%"></td>
      <td align=center><img src="" width="40%"></td>
      <td align=center><img src="" width="40%"></td>
    </tr>
</table>


## 2024-1학기 - 캡스톤디자인1
<details>
    <summary>각 팀원별 진행 과정 [펼치기/접기]</summary>

<!-- 순서:  KimTeddy / MoonScott / iamgodjinsu / minjoll / jungminhye / 공통-->
| 주차 | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=KimTeddy"><code>KimTeddy</code></a><br>(나, 팀장) | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=MoonScott"><code>MoonScott</code></a><br>(총무) | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=iamgodjinsu"><code>iamgodjinsu</code></a> | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=minjoll"><code>minjoll</code></a> | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=jungminhye"><code>jungminhye</code></a> | 공통 |
|-:|-----|-----|-----|-----|-----|-|
| 1| 팀원 모으기<br>NUCLEO 보드 사용 방법 세미나 진행<br>|  |  |  |  | STM32CubeIDE 프로그램 사용 방법 익히기
| 2|  | 사용 전력량 계산 | 사용 전력량 계산 | 사용 전력량 계산 | AI 모델 형식 결정 | 필요 SPEC 분석
| 3|  |  | DMA 사용 연구 |  | 딥러닝 -> AI 모델 개발 | 부품 구매-1차
| 4| PCB 스키메틱-1차 | SleepMode 사용 연구 | SPI 카메라 작동 확인 | SleepMode 사용 연구 | AI 모델 정확도 개선 |
| 5| PCB 스키메틱-2차 | // | SPI 카메라 작동 연구 | // | AI 모델 RAM 차지 용량 낮추기 | 부품 구매-2차
| 6| 만능기판 납땜 | // | DCMI 카메라 테스트 | // | 최종 AI 모델 차지 용량 확인 |
| 7| MPPT 찾아보기 | // | // | // |  |
| 8| PCB 스키메틱-3차<br>PCB 디자인-1차 | nRF24L01 사용 연구 | // | nRF24L01 사용 연구 |  |
| 9| PCB 디자인-2차 | // | OV2640 사용 연구 | // | Cube.AI 예제 사용자 함수 분석 |
|10| PCB 디자인-3차<br>PCB 주문 | // | // | // |  | 부품 구매-3차
|11| - PCB 납땜, 테스트, 디버깅<br>- FP-AI-VISION코드 현재 보드에 맞게 수정<br>- CubeMX 전체 기능 통합 설정+핀 설정, 기능 사용 방법 README.md 작성<br>- 배터리 전압 확인 ADC 코드 작성 | OV2640 사용 연구 | //, 이미지 데이터 UART 전송 시도 | // | FP-AI-VISION코드 현재 보드에 맞게 수정 | 
|12|  |  |  |  |  | 발표 준비
|13|  |  |  |  |  | 최종 발표

</details>

## 2024-여름방학
<details>
    <summary>각 팀원별 진행 과정 [펼치기/접기]</summary>

<!-- 순서:  KimTeddy / MoonScott / iamgodjinsu / minjoll / jungminhye / 공통-->
<table>
  <thead>
    <tr>
      <th>주차</th>
      <th><a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=KimTeddy"><code>KimTeddy</code></a><br>(나, 팀장)</th>
      <th><a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=MoonScott"><code>MoonScott</code></a><br>(총무)</th>
      <th><a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=iamgodjinsu"><code>iamgodjinsu</code></a></th>
      <th><a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=minjoll"><code>minjoll</code></a></th>
      <th><a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=jungminhye"><code>jungminhye</code></a></th>
      <th>공통</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>6/24~6/30</td>
      <td>2차 PCB 설계</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>7/1 ~ 7/7</td>
      <td>2차 PCB 설계</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>7/8 ~7/14</td>
      <td>2차 PCB 설계</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>7/15~7/21</td>
      <td>
        <ul>
          <li>OpenCV 세팅하기</li>
          <li>RF_TX가 보내고 RF_RX가 받기 성공하면 받았다고 ack 보낸 내용을 RF_TX가 받아서 통신 종료하기 성공</li>
        </ul>
      </td>
      <td>
        <ul>
          <li>보고서 작성 시작하기</li>
          <li>UI 추가 수정(배터리 추가)</li>
        </ul>
      </td>
      <td>H7A3에서 OV2640 JPEG 이미지 받기</td>
      <td>
        <ul>
          <li>Qt 설치 후 방법 알려주기</li>
          <li>UI에서 버튼 누르면 이미지 바꾸기 성공</li>
        </ul>
      </td>
      <td>Visual Studio에서 YOLO 시도 시작</td>
      <td>
        <ul>
          <li>OpenCV 설치하기</li>
          <li>Qt 설치하기</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td>7/22<br>~7/28</td>
      <td></td>
      <td></td>
      <td>7/28:H7A3에서 OV2640 JPEG 성공공</td>
      <td></td>
      <td></td>
      <td>7/22(월) 회의</td>
    </tr>
    <tr>
      <td>7/29<br>~8/4</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td>8/4(일) 회의</td>
    </tr>
    <tr>
      <td>8/12<br>~8/18</td>
      <td>
              <ul>
              <li>8/14:RF USB PCB v1 설계 시작</li>
              <li>8/18:보드용 PCB v2.0.1 설계 시작</li>
              </ul>
      </td>
      <td></td>
      <td>8/12:JPEG 디코딩 커뮤니티 답변 받음</td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>8/19<br>~8/25</td>
      <td>8/23:PCB v2.0 첫 납땜
              <ul>
                      <li>MCU 실장 정상 작동</li>
                      <li>PIR 오작동</li>
              </ul>
              8/24:안테나 회로 정상 확인<br>
      </td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>8/26 ~ 9/1</td>
      <td>8/27(화):
                <ul>
                  <li>3.3V 벅-부스트 스위칭 레귤레이터</li>
                  <li>USB Virtual com port 통신</li>
                  <li>USB data plus 핀을 통한 USB 연결 신호 회로 작동</li>
                  <li>OV2640, RF 모듈 전원 on/off 회로 작동</li>
                  <li>2.8V 레귤레이터 작동</li>
                  <li>단색 LED 4개, RGB LED 작동 확인 및 함수 코딩</li>
                  <li>배터리 ADC</li>
                </ul>
              8/28(수):
            <ul>
              <li>OV2640 I2C 레지스터 세팅 정상</li>
              <li>1.3V 레귤레이터 작동</li>
              <li>배터리 소켓 뒤집어서 납땜</li>
                <li>ADC 핀 이동</li>
                <li>USB C CC1,CC2 풀다운 추가</li>
            </ul>
          8/29(목):
              PIR 센서 신호 인버터 회로 정상 작동
          </li>
        </ul>
      </td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td>8/29(목) 회의</td>
    </tr>
  </tbody>
</table>

<!--
| 주차 | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=KimTeddy"><code>KimTeddy</code></a><br>(나, 팀장) | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=MoonScott"><code>MoonScott</code></a><br>(총무) | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=iamgodjinsu"><code>iamgodjinsu</code></a> | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=minjoll"><code>minjoll</code></a> | <a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=jungminhye"><code>jungminhye</code></a> | 공통 |
|-:|-----|-----|-----|-----|-----|-|
|6/24~6/30| 2차 PCB 설계 |  |  |  |  ||
|7/1 ~ 7/7| 2차 PCB 설계 |  |  |  |  ||
|7/8 ~7/14| 2차 PCB 설계 |  |  |  |  ||
|7/15~7/21| - OpenCV 세팅하기<br>- RF_TX가 보내고 RF_RX가 받기 성공하면 받았다고 ack 보낸 내용을 RF_TX가 받아서 통신 종료하기 성공 | - 보고서 작성 시작하기<br> - UI 추가 수정(배터리 추가) |  H7A3에서 OV2640 JPEG 이미지 받기 | - Qt 설치 후 방법 알려주기<br> - UI에서 버튼 누르면 이미지 바꾸기 성공 | Visual Studio에서 YOLO 시도 시작 | - OpenCV 설치하기<br>- Qt 설치하기 |
|8/26 ~ 9/1| [PCB 검증]<br>-8/28:•OV2640회로 중 I2C 레지스터 세팅 정상<br>•1.3V 레귤레이터 작동<br>-8/29:<br>•PIR 센서 신호 인버터 회로 정상 작동 |  |  |  |  ||
-->
</details>

## 2024-2학기 - 캡스톤디자인2
<details>
    <summary>각 팀원별 진행 과정 [펼치기/접기]</summary>

<!-- 순서:  KimTeddy / MoonScott / iamgodjinsu / minjoll / jungminhye / 공통-->
<table>
  <thead>
    <tr>
      <th>주차</th>
      <th><a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=KimTeddy"><code>KimTeddy</code></a><br>(나, 팀장)</th>
      <th><a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=iamgodjinsu"><code>iamgodjinsu</code></a></th>
      <th><a href="https://github.com/KimTeddy/2024_A.RM.I/commits?author=jungminhye"><code>jungminhye</code></a></th>
      <th>공통</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>9/2~9/8</td>
      <td>PCBv2 MPPT 회로 납땜, 1:1 RF 이미지 전송, 서버 전체 코드 통합</td>
      <td>Windows C++환경 UART 데이터 배열 저장</td>
      <td>Windows C++환경 YOLOv4 작동</td>
      <td>ESW 신청</td>
    </tr>
    <tr>
      <td>9/9~9/15</td>
      <td>//</td>
      <td>Qt 공부</td>
      <td>-</td>
      <td></td>
    </tr>
    <tr>
      <td>[추석] 9/16~9/22</td>
      <td>DCMI 작동 확인용 OV2640 모듈 단자 와이어링</td>
      <td>Qt 공부</td>
      <td>CGAN 공부</td>
      <td></td>
    </tr>
    <tr>
      <td>9/23~9/29</td>
      <td>PCB 디버깅(DCMI 작동 확인)</td>
      <td></td>
      <td>-</td>
      <td>4주차 PPT 제작, 9/25(수) 회의</td>
    </tr>
    <tr>
      <td>9/30~10/6</td>
      <td>PCB 디버깅(PIR회로 재시도, OV2640회로 작동 확인)</td>
      <td>1:N 통신 알고리즘 구현</td>
      <td>CGAN 이용 훈련데이터 생성(Edge Device NN모델 성능 강화)</td>
      <td>5주차 PPT 제작</td>
    </tr>
    <tr>
      <td>10/7~10/13</td>
      <td>SERVER PCB 주문, PCB v2.1 수정 후 주문</td>
      <td></td>
      <td></td>
      <td>6주차 PPT 제작</td>
    </tr>
    <tr>
      <td>10/14~10/20</td>
      <td>PCB v2.1 납땜</td>
      <td></td>
      <td></td>
      <td>7주차 PPT 제작</td>
    </tr>
    <tr>
      <td>10/21~10/27</td>
      <td></td>
      <td></td>
      <td></td>
      <td>8주차 PPT 제작, ESW오프라인 심사</td>
    </tr>
    <tr>
      <td>10/28~11/3</td>
      <td></td>
      <td></td>
      <td></td>
      <td>9주차 PPT 제작</td>
    </tr>
    <tr>
      <td>11/4~11/10</td>
      <td></td>
      <td></td>
      <td></td>
      <td>10주차 PPT 제작</td>
    </tr>
    <tr>
      <td>11/11~11/17</td>
      <td></td>
      <td></td>
      <td></td>
      <td>11주차 PPT 제작</td>
    </tr>
  </tbody>
</table>

</details>


### pcb
<table>
    <tr align=center>
        <th width=35%>1차 PCB 앞면</th>
        <th width=35%>1차 PCB 뒷면</td>
    </tr>
    <tr>
      <td align=center><img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/887c4f98-7ed3-4951-9eee-dfe40d755ce4" width="%"></td>
      <td align=center><img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/7fb04112-5832-4a31-a653-356fcf7f8705" width="%"></td>
    </tr>
</table>
  <!-- 
![240509_ARMI_PCB_0603_5](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/887c4f98-7ed3-4951-9eee-dfe40d755ce4)
![240509_ARMI_PCB_0603_6](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/7fb04112-5832-4a31-a653-356fcf7f8705)
 -->

### 구성도
- HW 구성도<br>
&nbsp;<img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/6d7bc5bb-5b66-4aa1-8b81-71c2848d737e" width="60%">

- SW 구성도<br>
&nbsp;<img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/8eb6e8f9-d6c1-46a1-b9cd-afa93e3de618" width="60%">

- AI Network Model<br>
&nbsp;<img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/f937bddf-4006-49fb-a1fd-5cb3fe8f77e1" width="30%">
  <!-- ![HW구성도](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/6d7bc5bb-5b66-4aa1-8b81-71c2848d737e) -->
  <!-- ![SW구성도](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/8eb6e8f9-d6c1-46a1-b9cd-afa93e3de618) -->
  <!-- ![ai_network_model_test_quant_msy tflite_c_info json](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/f937bddf-4006-49fb-a1fd-5cb3fe8f77e1) -->

## 전류 측정
<table>
    <tr align=center>
        <th width=35%>피크 전류</th>
        <th width=35%>Neural Network 연산 시 전류</td>
    </tr>
    <tr>
      <td align=center><img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/cfd80b52-72ba-45be-a965-1033bc8441f8" width="35%"></td>
      <td align=center><img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/caf8739e-6835-4652-8b9e-8db89d9aea5f" width="35%"></td>
    </tr>
</table>
###
  <!-- 
![KakaoTalk_20240604_165802999_012](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/cfd80b52-72ba-45be-a965-1033bc8441f8)
![KakaoTalk_20240604_1658029992](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/caf8739e-6835-4652-8b9e-8db89d9aea5f)
 -->

## 2024-2학기 - 캡스톤디자인2
- 컴퓨터와 통신
