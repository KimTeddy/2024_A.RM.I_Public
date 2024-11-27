/*
 * relay.h
 *
 *  Created on: Oct 18, 2024
 *      Author: witha
 */

#ifndef INC_ARMI_RELAY_H_
#define INC_ARMI_RELAY_H_
//#include <stdint.h>

#include "main.h"
#include "nrf24l01p.h"

#include "armi_gpio.h"
#include "armi_uart.h"

#define MAX_RETRIES 5   // 최대 재전송 횟수

extern uint8_t addr_broad[5];
extern uint8_t addr_dev[5];
//armi_tx_
int receive_data_and_check(uint8_t *rx_address);
int rx_print(void);
int rx_ing(int edge1_is_close);
void tx_to_edge(int tx_status, int edge1_is_close);
void image_rx_fun(void);
int edge_rx_set(int edge_stat);
void transmit_with_ack(uint8_t *tx_data);
void send_ack_to(uint8_t *ack_addr);
void transmit_with_manual_ack(uint8_t *tx_data);

int count_non_zero_data(uint8_t *array, int size);
#endif /* INC_ARMI_RELAY_H_ */
