/*
 * armi_rf.h
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#ifndef INC_ARMI_RF_H_
#define INC_ARMI_RF_H_

#include "main.h"
#include "nrf24l01p.h"

#include "armi_uart.h"
#include "armi_dcmi.h"
#include "armi_relay.h"
//RF
#define RF_TX false
#define RF_RX true

#define RF_TIMEOUT 50

//RF------------------------------------------------
extern bool armi_rf_mode;
extern uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH];
extern uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH];
extern int ok;
extern int num;
extern int row;
extern int armi_timeout_num;

void armi_rf_set(bool rf_mode);
void armi_rf_dir(bool rf_mode);
void armi_rf_rx_timeout();
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void armi_image_tx();

#endif /* INC_ARMI_RF_H_ */
