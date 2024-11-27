/*
 * armi_rf.c
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#include "armi_rf.h"

//RF------------------------------------------------
bool armi_rf_mode = RF_TX;
uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH] = { 0, };
uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH] = "4HIARMI";
int ok = 0;
int num = 1;
int row = 0;
int armi_timeout_num = 0;

//RF
void armi_rf_set(bool rf_mode) {
	if (rf_mode == RF_TX)
		nrf24l01p_tx_init(2500, _2Mbps);
	else
		nrf24l01p_rx_init(2500, _2Mbps);
	armi_rf_mode = rf_mode;
}
void armi_rf_dir(bool rf_mode) {
	if (rf_mode != armi_rf_mode) {
		if (rf_mode == RF_TX)
			nrf24l01p_ptx_mode();
		else
			nrf24l01p_prx_mode();
		armi_rf_mode = rf_mode;
	}
}
void armi_rf_rx_timeout() {
	uint32_t start_time = HAL_GetTick();

	while (1) {
		//nrf24l01p_rx_receive(rx_data);
		//HAL_Delay(1);
		if (rx_data[0] != 0) {//if received
			armi_timeout_num=0;
			return;
		}

		if ((HAL_GetTick() - start_time) > RF_TIMEOUT) {
			my_printf(".");
			armi_timeout_num++;
			break;
		}
	}
}
void armi_image_tx() {
	armi_rf_set(RF_TX);
	//HAL_Delay(50);

//	sprintf(tx_data,
//			"%1d%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\0",
//			num, frameBuffer[0], frameBuffer[1], frameBuffer[2], frameBuffer[3],
//			frameBuffer[4], frameBuffer[5], frameBuffer[6], frameBuffer[7],
//			frameBuffer[8], frameBuffer[9], frameBuffer[10], frameBuffer[11],
//			frameBuffer[12], frameBuffer[13], frameBuffer[14]);

	tx_data[0] = num;
	for (int i = 0; i < 30; i++) {
		tx_data[i + 1] = frameBuffer_jpeg[i];
	}

	while (1) {
		armi_rf_set(RF_TX);
		//HAL_Delay(10);
		nrf24l01p_tx_transmit(tx_data);
		HAL_Delay(1);
		//my_printf("tx)Check Num:\'%c\', \"%s\"\r\n", tx_data[0], &tx_data[1]);
		//my_printf("tx)Check Num:\'%d\', \"%02x%02x\"\r\n", tx_data[0], tx_data[row + 1], tx_data[row + 2]);
		//my_printf(
		//		"tx)Check Num:\'%d\', \"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\"\r\n",
		//		tx_data[0], tx_data[row + 1], tx_data[row + 2],
		//		tx_data[row + 3], tx_data[row + 4], tx_data[row + 5],
		//		tx_data[row + 6], tx_data[row + 7], tx_data[row + 8],
		//		tx_data[row + 9], tx_data[row + 10], tx_data[row + 11],
		//		tx_data[row + 12], tx_data[row + 13], tx_data[row + 14],
		//		tx_data[row + 15]);

		armi_rf_set(RF_RX);
		HAL_Delay(20);
		for (int i = 0; i < 500; i++) {
			nrf24l01p_rx_receive(rx_data);
			/*
			 armi_rf_rx_timeout();
			 if(armi_timeout_num>9){
			 HAL_Delay(300);
			 armi_timeout_num=0;
			 ok = 1;
			 }
			 */

			if (rx_data[0] == (num) && rx_data[1] == 'O' && rx_data[2] == 'K') {
				HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
				//my_printf("ack: %s\r\n", &rx_data[1]);
				rx_data[0] = 0;
				rx_data[1] = 0;
				rx_data[2] = 0;
				ok = 1;
			}

			if (row > bufferPointer)
				return;
			if (rx_data[0] == ('F') && rx_data[1] == 'I' && rx_data[2] == 'N')
				return;
		}
		if (ok == 1) {
			row += 30;
			num++;
			if (num > 9)
				num = 1;

//			sprintf(tx_data,
//					"%1d%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\0",
//					num, frameBuffer[row + 0], frameBuffer[row + 1],
//					frameBuffer[row + 2], frameBuffer[row + 3],
//					frameBuffer[row + 4], frameBuffer[row + 5],
//					frameBuffer[row + 6], frameBuffer[row + 7],
//					frameBuffer[row + 8], frameBuffer[row + 9],
//					frameBuffer[row + 10], frameBuffer[row + 11],
//					frameBuffer[row + 12], frameBuffer[row + 13],
//					frameBuffer[row + 14]);

			tx_data[0] = num;
			for (int i = 0; i < 30; i++) {
				tx_data[i + 1] = frameBuffer_jpeg[row + i];
			}

			ok = 0;
		}
	}
}

//INTERRUPT
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER) {
		//HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		//nrf24l01p_rx_receive(rx_data);
		if (armi_rf_mode == RF_TX)
			nrf24l01p_tx_irq();
		else {
//			HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
//			nrf24l01p_rx_receive(rx_data);
		}
	}
}
