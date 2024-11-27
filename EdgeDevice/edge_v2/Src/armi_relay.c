/*
 * relay.c
 *
 *  Created on: Oct 18, 2024
 *      Author: witha
 */

#include "armi_relay.h"

uint8_t addr_broad[5] = {0, };
uint8_t addr_dev[5] = {0, };

int receive_data_and_check(uint8_t *rx_address) {
	static uint8_t rx_data[32];  // 정적 배열 선언
	uint8_t status;
	uint8_t data_size;
	static uint8_t tx_data[32];
	while (1) {
		// NRF24L01+ STATUS 레지스터 읽기
		status = read_register(NRF24L01P_REG_STATUS);

		// RX_DR 비트(6번째 비트)가 1인지 확인
		if (status & (1 << 6)) {
			// 데이터 수신
			nrf24l01p_rx_receive(rx_data);

			// STATUS 레지스터의 RX_DR 비트 클리어
			write_register(NRF24L01P_REG_STATUS, (1 << 6));

			// 비영(0이 아닌) 데이터 개수 계산
			data_size = count_non_zero_data(rx_data, 32);

			// 수신된 데이터 출력
			my_printf("rx data::");
			for (int i = 0; i < data_size; i++) {
				my_printf("%02X ", rx_data[i]);  // 예: 0xE1, 0xE2
			}
			my_printf("\r\n");
			my_printf("data size::%d byte\r\n", data_size);

			// 조건 검사: 첫 번째 값이 0xE1이고 마지막 값이 0xD1인지 확인
			if (rx_data[0] == 0xE1 && rx_data[data_size - 1] == 0xD1) {

				memcpy(tx_data, rx_data, data_size);
				my_printf("tx data::");                 //0XE1, 0XD1,0XE1 이 나와야함
				tx_data[data_size] = 0xE1;
				for (int i = 0; i < data_size + 1; i++) {
					my_printf("%02X ", tx_data[i]);
				}
				my_printf("\r\n");

				HAL_Delay(1000);
				my_printf("START TO TX\r\n");
				//nrf24l01p_tx_init(2500, _1Mbps, rx_address);

				for (int i = 0; i < 10000; i++) {
					HAL_Delay(1);
					nrf24l01p_tx_transmit(tx_data);    //0xe1,0xeD1,0XE1 보내기
				}

				return 1;  // 조건을 만족하면 1 반환

			} else {
				my_printf("DON'T TX this data\r\n");         //0xE1,0XE2 는 미전송
				memset(rx_data, 0, sizeof(rx_data));
				//	nrf24l01p_rx_init(2500, _1Mbps, rx_address, rx_address);

				return 0;  // 조건을 만족하지 않으면 0 반환
			}
		}
	}
}

int rx_print(void) {
	static uint8_t rx_data[32];  // 정적 배열 선언
	uint8_t status;
	uint8_t data_size;
	uint8_t rx_flag = 0;
	uint8_t edge1 = 0;

	do {
		// NRF24L01+ STATUS 레지스터 읽기
		status = read_register(NRF24L01P_REG_STATUS);

		// RX_DR 비트(6번째 비트)가 1이면 데이터 수신
		if (status & (1 << 6)) {
			// 데이터 수신
			nrf24l01p_rx_receive(rx_data);

			// STATUS 레지스터에서 파이프 번호 추출 (비트 1~3)
			uint8_t pipe = (status >> 1) & 0x07;  // 파이프 번호는 0~5

			switch (pipe) {
			case 0:  // P0에서 수신된 데이터 처리
				my_printf("EDGE1 IS CLOSE \r\n");
				edge1 = 1;
				break;
			case 1:  // P1에서 수신된 데이터 처리
				my_printf("EDGE2 IS CLOSE \r\n");
				edge1 = 0;
				break;
			default:
				my_printf("Other pipe: %d, data: %02x\r\n", pipe, rx_data[0]);
				break;
			}

			// STATUS 레지스터의 RX_DR 비트 클리어
			write_register(NRF24L01P_REG_STATUS, (1 << 6));

			// RX FIFO 비우기 (필요에 따라)
			nrf24l01p_flush_rx_fifo();

			// 데이터 수신 완료 플래그 설정
			rx_flag = 1;
		}
	} while (rx_flag != 1);

	data_size = count_non_zero_data(rx_data, 32);

	// 수신된 데이터 출력
	my_printf("rx data::");
	for (int i = 0; i < data_size; i++) {
		my_printf("%02X ", rx_data[i]);  // 예: 0xE1, 0xE2
	}
	my_printf("\r\n");

	memset(rx_data, 0, sizeof(rx_data));

	if (edge1 == 1) {
		return 1;
	} else
		return 0;

}

int rx_ing(int edge1_is_close) {
	static uint8_t rx_data[32];  // 정적 배열 선언
	uint8_t status;
	uint8_t data_size;
	uint8_t rx_flag = 0;
	uint8_t edge1_request = 0;
	uint8_t edge2_request = 0;

	// 첫 수신 확인
	do {
		// NRF24L01+ STATUS 레지스터 읽기
		status = read_register(NRF24L01P_REG_STATUS);

		// RX_DR 비트(6번째 비트)가 1이면 데이터 수신
		if (status & (1 << 6)) {
			// 데이터 수신
			nrf24l01p_rx_receive(rx_data);

			// STATUS 레지스터에서 파이프 번호 추출 (비트 1~3)
			uint8_t pipe = (status >> 1) & 0x07;  // 파이프 번호는 0~5

			switch (pipe) {
			case 0:  // P0에서 수신된 데이터 처리
				my_printf("EDGE1 IMAGE request \r\n");
				edge1_request = 1;
				break;
			case 1:  // P1에서 수신된 데이터 처리
				my_printf("EDGE2 IMAGE request \r\n");
				edge2_request = 1;
				break;
			default:
				my_printf("Other pipe: %d, data: %02x\r\n", pipe, rx_data[0]);
				break;
			}

			// STATUS 레지스터의 RX_DR 비트 클리어
			write_register(NRF24L01P_REG_STATUS, (1 << 6));

			// RX FIFO 비우기 (필요에 따라)
			nrf24l01p_flush_rx_fifo();

			// 데이터 수신 완료 플래그 설정
			rx_flag = 1;
		}
	} while (rx_flag != 1);

	data_size = count_non_zero_data(rx_data, 32);

	// 수신된 데이터 출력
	my_printf("rx data::");
	for (int i = 0; i < data_size; i++) {
		my_printf("%02X ", rx_data[i]);  // 예: 0xE1, 0xE2
	}
	my_printf("\r\n");
	my_printf("data size::%d byte\r\n", data_size);
	memset(rx_data, 0, sizeof(rx_data));

	// 100ms 동안 추가적인 수신 확인
	uint32_t start_time = HAL_GetTick();  // 현재 시간 기록
	while (HAL_GetTick() - start_time < 100) {
		// NRF24L01+ STATUS 레지스터 읽기
		status = read_register(NRF24L01P_REG_STATUS);

		// RX_DR 비트(6번째 비트)가 1이면 데이터 수신
		if (status & (1 << 6)) {
			// 추가 데이터 수신
			nrf24l01p_rx_receive(rx_data);

			// STATUS 레지스터에서 파이프 번호 추출 (비트 1~3)
			uint8_t pipe = (status >> 1) & 0x07;  // 파이프 번호는 0~5

			switch (pipe) {
			case 0:  // P0에서 수신된 데이터 처리
				if (rx_data[0] == 0xa1)
					my_printf("EDGE1 IMAGE TX request \r\n");
				edge1_request = 1;
				break;
			case 1:  // P1에서 수신된 데이터 처리
				if (rx_data[0] == 0xa1)
					my_printf("EDGE2 IMAGE TX request \r\n");
				edge2_request = 1;
				break;
			default:
				my_printf("Other pipe: %d, data: %02x\r\n", pipe, rx_data[0]);
				break;
			}

			// STATUS 레지스터의 RX_DR 비트 클리어
			write_register(NRF24L01P_REG_STATUS, (1 << 6));

			// RX FIFO 비우기 (필요에 따라)
			nrf24l01p_flush_rx_fifo();
		}
	}

	if (edge1_request == 1 && edge2_request == 0) {
		return 1;
	}

	else if (edge1_request == 0 && edge2_request == 1) {
		return 2;
	}

	else if (edge1_request == 1 && edge2_request == 1) {
		return 3;
	}

	else {
		return 0;

	}

}

void image_rx_fun(void) {
	static uint8_t rx_data[32];  // 정적 배열 선언
	uint8_t status;
	uint8_t data_size;
	uint8_t rx_flag = 0;

	// 첫 수신 확인
	do {
		// NRF24L01+ STATUS 레지스터 읽기
		status = read_register(NRF24L01P_REG_STATUS);

		// RX_DR 비트(6번째 비트)가 1이면 데이터 수신
		if (status & (1 << 6)) {
			// 데이터 수신
			nrf24l01p_rx_receive(rx_data);

			// STATUS 레지스터에서 파이프 번호 추출 (비트 1~3)
			uint8_t pipe = (status >> 1) & 0x07;  // 파이프 번호는 0~5

			switch (pipe) {
			case 0:  // P0에서 수신된 데이터 처리
				my_printf("EDGE1 IMAGE transmit \r\n");

				break;
			case 1:  // P1에서 수신된 데이터 처리
				my_printf("EDGE2 IMAGE transmit \r\n");

				break;
			default:
				my_printf("Other pipe: %d, data: %02x\r\n", pipe, rx_data[0]);
				break;
			}

			// STATUS 레지스터의 RX_DR 비트 클리어
			write_register(NRF24L01P_REG_STATUS, (1 << 6));

			// RX FIFO 비우기 (필요에 따라)
			nrf24l01p_flush_rx_fifo();

			// 데이터 수신 완료 플래그 설정
			rx_flag = 1;
		}
	} while (rx_flag != 1);

	data_size = count_non_zero_data(rx_data, 32);

	// 수신된 데이터 출력
	my_printf("rx data::");
	for (int i = 0; i < data_size; i++) {
		my_printf("%02X ", rx_data[i]);  // 예: 0xE1, 0xE2
	}
	my_printf("\r\n");
	my_printf("data size::%d byte\r\n", data_size);
	memset(rx_data, 0, sizeof(rx_data));
}

int edge_rx_set(int edge_stat) {
	int status = 0;
	static uint8_t rx_data[32];
	int data_size = 0;
	// 초기화 - PC와 통신 여부에 따라 설정
	memset(rx_data, 0, sizeof(rx_data));
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(50);

	int rx_flag = 0;
	nrf24l01p_rx_init(2500, _1Mbps, addr_broad);

	do {
		// NRF24L01+ STATUS 레지스터 읽기
		status = read_register(NRF24L01P_REG_STATUS);

		// RX_DR 비트(6번째 비트)가 1이면 데이터 수신
		if (status & (1 << 6)) {
			// 데이터 수신
			nrf24l01p_rx_receive(rx_data);

			// STATUS 레지스터의 RX_DR 비트 클리어
			write_register(NRF24L01P_REG_STATUS, (1 << 6));

			// RX FIFO 비우기 (필요에 따라)
			nrf24l01p_flush_rx_fifo();

			// 데이터 수신 완료 플래그 설정
			rx_flag = 1;
		}
	} while (rx_flag != 1);

	// 수신 데이터 크기 확인 및 출력
	data_size = count_non_zero_data(rx_data, 32);
	my_printf("rx data::");
	for (int i = 0; i < data_size; i++) {
		my_printf("%02X ", rx_data[i]);
	}
	my_printf("\r\n");

	// 수신 데이터 조건에 따라 ACK 전송 및 반환 값 설정
	if (rx_data[0] == 0xd2) {
		send_ack_to(addr_broad);  // ACK 전송
		return 2;  // 이미지 송신
	} else if (rx_data[0] == 0xd0) {

		send_ack_to(addr_broad);  // ACK 전송

		return 0;  // 다시 수신
	} else {  // 이벤트 기다리기
		send_ack_to(addr_broad);  // ACK 전송
		return 1;
	}

	memset(rx_data, 0, sizeof(rx_data));  // 데이터 초기화
}

void transmit_with_ack(uint8_t *tx_data) {
	uint8_t status;
	uint32_t start_time = HAL_GetTick();

	while (1) {
		// 데이터 전송
		nrf24l01p_tx_transmit(tx_data);

		// 전송 완료 여부 확인
		while (1) {
			// STATUS 레지스터 읽기
			status = read_register(NRF24L01P_REG_STATUS);

			// TX_DS 비트(5번째 비트)가 1이면 전송 성공 및 ACK 수신
			if (status & (1 << 5)) {
				// 전송 성공 시 TX_DS 비트를 클리어
				write_register(NRF24L01P_REG_STATUS, (1 << 5));
				my_printf("ACK received. Transmission successful.\r\n");
				return; // ACK 수신했으므로 함수 종료
			}

			// 전송 실패 시 (맥스 리트라이 초과)
			if (status & (1 << 4)) {  // MAX_RT 비트가 1이면 최대 재시도 도달
				// MAX_RT 비트를 클리어
				write_register(NRF24L01P_REG_STATUS, (1 << 4));

				my_printf("Max retries reached. Retrying...\r\n");
				break; // 내부 while 루프를 벗어나 재전송 시도
			}

			// 타임아웃 조건 (예: 100ms)
			if ((HAL_GetTick() - start_time) > 1000) {
				my_printf("Timeout. Retrying...\r\n");
				break; // 내부 while 루프를 벗어나 재전송 시도
			}
		}

		// RX FIFO 비우기 (필요시)
		nrf24l01p_flush_rx_fifo();
	}
}

void send_ack_to(uint8_t *ack_addr) {
	uint8_t broad_addr[5] = "step1";
	uint8_t ack_data[32] = { 0xe1, 0 };  // 예시 ACK 데이터
	ack_data[0] = ack_data[0] | armi_dipsw_devnum();  // 추가 데이터 처리

	int retry_count = 0;    // 재전송 카운터

	while (retry_count < MAX_RETRIES) {
		// 송신 모드로 전환
		nrf24l01p_tx_init(2500, _1Mbps, broad_addr);
		HAL_Delay(10);  // 안정화 시간

		nrf24l01p_tx_transmit(ack_data);    // ACK 데이터 전송

		// TX 전송 완료 대기
		uint32_t start_time = HAL_GetTick();  // 시작 시간 기록
		while (!(read_register(NRF24L01P_REG_STATUS) & (1 << 5))) {
			// Timeout 조건: 10ms 이상 대기하면 중단
			if (HAL_GetTick() - start_time > 10) {
				my_printf("Transmission timeout. Retrying...\r\n");
				break;
			}
		}

		// TX_DS 비트 확인 및 클리어
		if (read_register(NRF24L01P_REG_STATUS) & (1 << 5)) {
			write_register(NRF24L01P_REG_STATUS, (1 << 5));  // TX_DS 비트 클리어
			my_printf("ACK transmitted successfully.\r\n");
			return;  // ACK 전송 성공 후 종료
		}

		// 재전송 카운트 증가
		retry_count++;
		if (retry_count >= MAX_RETRIES) {
			my_printf("Max retries reached. ACK transmission failed.\r\n");
			return;  // 최대 재전송 횟수 초과 시 실패
		}
	}
}

void transmit_with_manual_ack(uint8_t *tx_data) {
	uint8_t status;
	uint8_t ack_data[32] = { 0 };  // ACK 데이터를 수신할 버퍼
	uint32_t start_time;
	uint8_t addr1[5] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xE1 };
	int retry_count = 0;
	const int max_retries = 5;  // 최대 재전송 횟수 설정

	while (retry_count < max_retries) {
		// 송신 전 TX, RX 플래그 클리어
		nrf24l01p_clear_tx_ds();
		nrf24l01p_clear_rx_dr();
		nrf24l01p_clear_max_rt();

		// 데이터 전송
		nrf24l01p_tx_init(2500, _1Mbps, addr1);
		nrf24l01p_tx_transmit(tx_data);

		// TX 전송 완료 대기
		start_time = HAL_GetTick();
		while (1) {
			status = read_register(NRF24L01P_REG_STATUS);

			// TX_DS 비트(5번째 비트)가 1이면 데이터 전송 완료됨
			if (status & (1 << 5)) {
				nrf24l01p_clear_tx_ds();  // TX_DS 비트 클리어
				break;  // 전송 완료 후 수신 모드로 전환 준비
			}

			// 타임아웃 조건 설정 (예: 10ms)
			if ((HAL_GetTick() - start_time) > 10) {
				my_printf(
						"Transmission timeout. Data not sent. Retrying...\r\n");
				retry_count++;
				break;  // 타임아웃 발생 시 재전송을 위해 바깥 루프로 재진입
			}
		}

		// 송신 후 수신 모드 전환 (ACK 수신 대기)
		nrf24l01p_rx_init(2500, _1Mbps, addr1);

		// ACK 수신 대기
		start_time = HAL_GetTick();
		while (1) {
			status = read_register(NRF24L01P_REG_STATUS);

			// MAX_RT 발생 시 재전송 시도
			if (status & (1 << 4)) {
				my_printf("Max retransmit reached. Retrying...\r\n");
				nrf24l01p_clear_max_rt();  // MAX_RT 비트 클리어
				nrf24l01p_ptx_mode();  // 송신 모드로 전환
				retry_count++;
				break;  // 재전송을 위해 바깥 루프로 재진입
			}

			// RX_DR 비트(6번째 비트)가 1이면 ACK 데이터 수신됨
			if (status & (1 << 6)) {
				nrf24l01p_rx_receive(ack_data);  // ACK 데이터 수신
				nrf24l01p_clear_rx_dr();  // RX_DR 비트 클리어

				// 예상한 ACK 데이터인지 확인
				if (ack_data[0] == 0xa1) {
					my_printf("Transmission successful.\r\n");
					return;  // 전송 성공
				} else {
					my_printf("Received incorrect ACK data.\r\n");
					retry_count++;
					break;  // 잘못된 ACK 데이터 수신 시 재전송을 위해 바깥 루프로 재진입
				}
			}

			// 타임아웃 조건 설정 (예: 500ms)
			if ((HAL_GetTick() - start_time) > 500) {
				my_printf(
						"Transmission timeout. No ACK received. Retrying...\r\n");
				retry_count++;
				break;  // 타임아웃 발생 시 재전송을 위해 바깥 루프로 재진입
			}
		}
	}

	// 최대 재전송 횟수 초과 시 전송 실패 메시지 출력
	my_printf("Transmission failed after maximum retries.\r\n");
}

int count_non_zero_data(uint8_t *array, int size) {
	int count = 0;

	// 배열 내 0이 아닌 데이터를 만날 때까지 카운트
	for (int i = 0; i < size; i++) {
		if (array[i] == 0) {
			break; // 0이 아닌 데이터를 만나면 루프 종료
		}
		count++;
	}

	return count; // 0이 아닌 데이터가 나올 때까지의 개수 반환
}
