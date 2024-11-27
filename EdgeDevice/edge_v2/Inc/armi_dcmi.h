/*
 * armi_dcmi.h
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#ifndef INC_ARMI_DCMI_H_
#define INC_ARMI_DCMI_H_

#include "main.h"
#include "ov2640.h"

#include "armi_gpio.h"
#include "armi_uart.h"

//IMAGE
//#define RES160X120
#define RES320X240
//#define RES640X480
//#define RES800x600
//#define RES1024x768
//#define RES1280x960

#define DCMI_RAW 0
#define DCMI_JPEG 1
#define ARMI_SCCB_FAILURE_NUM 42

#ifdef RES160X120
extern enum imageResolution imgRes;
extern int imgRes_2;
extern uint8_t frameBuffer[RES_160X120];
#endif

#ifdef RES320X240
extern enum imageResolution imgRes;
extern int imgRes_raw;
extern uint8_t frameBuffer[76800];
extern uint8_t frameBuffer_jpeg[RES_1024x768];
#endif

#ifdef RES640X480
extern enum imageResolution imgRes;
extern int imgRes_2;
extern uint16_t frameBuffer[RES_640X480];
#endif

#ifdef RES800x600
extern enum imageResolution imgRes;
extern int imgRes_2;
extern uint8_t frameBuffer[RES_800x600];
#endif

#ifdef RES1024x768
extern enum imageResolution imgRes;
extern int imgRes_2;
extern uint8_t frameBuffer_raw[76800] = { 0 };
extern uint8_t frameBuffer[RES_1024x768];
#endif

#ifdef RES1280x960
extern enum imageResolution imgRes;
extern int imgRes_2;
extern uint16_t frameBuffer[RES_1280x960];
#endif

extern unsigned short mutex;
extern uint32_t bufferPointer;
extern uint32_t bufferPointer_jpeg;
extern unsigned short headerFound;

extern uint8_t rawjpeg;

void camera_capture(uint8_t rawjpeg);

#endif /* INC_ARMI_DCMI_H_ */
