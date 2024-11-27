/*
 * armi_dcmi.c
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */
#include "armi_dcmi.h"

#ifdef RES160X120
enum imageResolution imgRes=RES_160X120;
int imgRes_2 = 160 * 120 / 2;
uint8_t frameBuffer[RES_160X120] = { 0 };
#endif

#ifdef RES320X240
enum imageResolution imgRes = RES_1024x768;
int imgRes_raw = 320 * 240;
uint8_t frameBuffer[76800] = { 0 };//RAW
uint8_t frameBuffer_jpeg[RES_1024x768] = { 0 };
#endif

#ifdef RES640X480
enum imageResolution imgRes = RES_640X480;
int imgRes_2 = 640 * 480 / 2;
uint16_t frameBuffer[RES_640X480] = {0};
#endif

#ifdef RES800x600
enum imageResolution imgRes=RES_800x600;
int imgRes_2 = 800 * 600;
uint8_t frameBuffer[RES_800x600] = {0};
#endif

#ifdef RES1024x768
enum imageResolution imgRes=RES_1024x768;
int imgRes_2 = 1024 * 768;
uint8_t frameBuffer_raw[76800] = { 0 };
uint8_t frameBuffer[RES_1024x768] = {0};
#endif

#ifdef RES1280x960
enum imageResolution imgRes = RES_1280x960;
int imgRes_2 = 1280 * 960;
uint16_t frameBuffer[RES_1280x960] = {0};
#endif

unsigned short mutex = 1;
uint32_t bufferPointer = 76800;
uint32_t bufferPointer_jpeg = 0;
unsigned short headerFound = 0;

uint8_t rawjpeg = 1;

//IMAGE
void camera_capture(uint8_t rawjpeg) {
#ifdef DEBUG
	armi_led(2, 1);
#endif
	if (rawjpeg > 0) {
		bufferPointer_jpeg = 0;
		memset(frameBuffer_jpeg, 0, sizeof frameBuffer_jpeg);
		OV2640_CaptureSnapshot((uint32_t) frameBuffer_jpeg, imgRes);
		SCB_CleanInvalidateDCache_by_Addr((uint32_t*) frameBuffer_jpeg, imgRes);
		OV2640_CaptureSnapshot((uint32_t) frameBuffer_jpeg, imgRes);

		while (1) {
			if (headerFound == 0 && frameBuffer_jpeg[bufferPointer_jpeg] == 0xFF
					&& frameBuffer_jpeg[bufferPointer_jpeg + 1] == 0xD8) {
				headerFound = 1;
#ifdef DEBUG
				my_printf("Found header of JPEG file \r\n");
#endif
			}
			if (headerFound == 1 && frameBuffer_jpeg[bufferPointer_jpeg] == 0xFF
					&& frameBuffer_jpeg[bufferPointer_jpeg + 1] == 0xD9) {
				bufferPointer_jpeg = bufferPointer_jpeg + 2;
#ifdef DEBUG
				my_printf("Found EOF of JPEG file \r\n");
#endif
				headerFound = 0;
				break;
			}

			if (bufferPointer_jpeg >= 65535) {
				break;
			}
			bufferPointer_jpeg++;
		}
#ifdef DEBUG
		my_printf("Image size: %d bytes \r\n", bufferPointer_jpeg);
#endif
		//for (int i = 0; i < bufferPointer_jpeg; i++)
		//	my_printf("%02x", frameBuffer_jpeg[i]);
	} else {
		memset(frameBuffer, 0, sizeof frameBuffer);
		OV2640_CaptureSnapshot((uint32_t) frameBuffer, imgRes_raw);
		SCB_CleanInvalidateDCache_by_Addr((uint32_t*) frameBuffer, imgRes_raw);
		OV2640_CaptureSnapshot((uint32_t) frameBuffer, imgRes_raw);
#ifdef DEBUG
		//for (int i = 0; i < bufferPointer; i++)
		//	my_printf("%02x", frameBuffer[i]);
#endif
	}
}
