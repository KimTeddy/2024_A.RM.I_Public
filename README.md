# 2024_A.RM.I_Public
2024 캡스톤디자인 1, 2 졸업작품 2024_A.RM.I의 main 코드입니다.



## 2024-1학기 - 캡스톤디자인1
- 진행 과정<br>
  <!-- 순서:  KimTeddy / MoonScott / iamgodjinsu / minjoll / jungminhye -->
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
|12|  |  |  |  |  | 판넬 제작
|13|  |  |  |  |  | 작품 전시
|14|  |  |  |  |  |
### pcb
<table>
    <tr align=center>
        <th width=35%>피크 전류</th>
        <th width=35%>Neural Network 연산 시 전류</td>
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
      <td align=center><img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/dc2dc392-b3c3-4f36-a33f-604725e70a85" width="35%"></td>
      <td align=center><img src="https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/78ce6964-d8cf-4036-9db8-de0fb46e3ddb" width="35%"></td>
    </tr>
</table>
###
  <!-- 
![KakaoTalk_20240604_165802999_01](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/dc2dc392-b3c3-4f36-a33f-604725e70a85)
![KakaoTalk_20240604_165802999](https://github.com/KimTeddy/2024_A.RM.I_Public/assets/68770209/78ce6964-d8cf-4036-9db8-de0fb46e3ddb)
 -->

## 2024-2학기 - 캡스톤디자인2
- 컴퓨터와 통신
