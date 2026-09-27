/**
  ******************************************************************************
  * @file    test_functions.c
  * @brief   Test function definitions.
  * @author	 Jacopo Serafin
  * @date	 26/09/2026
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 Jacopo Serafin.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "test_functions.h"
#include "usart.h"
#include "i2c.h"
#include "main.h"
#include "GFX_FUNCTIONS.h"
#include <stdio.h>
#include "tests_config.h"

static uint8_t CalcCrcSGP40(uint8_t data[2]);


void TestUart1()
{
#if TEST_UART
	const uint8_t tx_buf[5] = {0x00, 0x01, 0x02, 0x03, 0x04};

	// Basic UART transaction
	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, &tx_buf[0], sizeof(tx_buf), 500);
#endif
}


void TestI2C()
{
#if TEST_I2C
	uint8_t tx_buff = 0x03;

	// Basic I2C transaction (no sensor communication)
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, 0x01<<1, 0x01, 0x01/*num of byte*/, &tx_buff, sizeof(tx_buff), 500);
#endif
}


void TestSGP40()
{
#if TEST_SGP40
	const char* TAG = "SGP40_Test";

	const uint8_t dev_address = 0x59;
	uint8_t tx_buff[2] = {0x36, 0x82};
	uint8_t rx_buff[9] = {0};

	// Read Serial Number. Timeout max 2ms
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, dev_address<<1, &tx_buff[0], 2, 500);
	status = HAL_I2C_Master_Receive(&hi2c1, dev_address<<1, &rx_buff[0], sizeof(rx_buff), 2);

	uint8_t crc_byte_1_2 = CalcCrcSGP40(&rx_buff[0]);
	uint8_t crc_byte_3_4 = CalcCrcSGP40(&rx_buff[3]);
	uint8_t crc_byte_5_6 = CalcCrcSGP40(&rx_buff[6]);

	// Check CRC match
	printf("%s: ser_numer byte 1-2 CRC [expected / received]: [0x%02X / 0x%02X]\n", TAG, rx_buff[2], crc_byte_1_2);
	printf("%s: ser_numer byte 3-4 CRC [expected / received]: [0x%02X / 0x%02X]\n", TAG, rx_buff[5], crc_byte_3_4);
	printf("%s: ser_numer byte 5-6 CRC [expected / received]: [0x%02X / 0x%02X]\n\n", TAG, rx_buff[8], crc_byte_5_6);
#endif
}


void TestSHT40_AD1B()
{
#if TEST_SHT40
	const char* TAG = "SHT40_Test";

	// Possible address (from datasheet): 0x44, 0x45, 0x46
	const uint8_t dev_address = 0x44;

	uint8_t tx_buff[1] = {0x89};
	uint8_t rx_buff[6] = {0};

	// Read Serial Number. Timeout max 2ms
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, dev_address<<1, &tx_buff[0], 1, 500);
	status = HAL_I2C_Master_Receive(&hi2c1, dev_address<<1, &rx_buff[0], sizeof(rx_buff), 500);

	uint8_t crc_byte_1_2 = CalcCrcSGP40(&rx_buff[0]);
	uint8_t crc_byte_3_4 = CalcCrcSGP40(&rx_buff[3]);

	// Check CRC match
	printf("%s: ser_numer byte 1-2 CRC [expected / received]: [0x%02X / 0x%02X]\n", TAG, rx_buff[2], crc_byte_1_2);
	printf("%s: ser_numer byte 3-4 CRC [expected / received]: [0x%02X / 0x%02X]\n", TAG, rx_buff[5], crc_byte_3_4);
#endif
}


void TestButton()
{
#if TEST_BTN
	const char* TAG = "Button_Test";

	uint8_t local_cnt = button_cnt;
	printf("%s: button_cnt : %d\n", TAG, local_cnt);
#endif
}




void TestDisplay()
{
#if TEST_DISPLAY
	// BackLight ON
	HAL_GPIO_WritePin(GPIOA, BCK_LIGHT_Pin, GPIO_PIN_SET);

	testAll();
#endif
}


static uint8_t CalcCrcSGP40(uint8_t data[2])
{
	uint8_t crc = 0xFF;
	for(int i = 0; i < 2; i++)
	{
		crc ^= data[i];
		for(uint8_t bit = 8; bit > 0; --bit)
		{
			if(crc & 0x80)
			{
				crc = (crc << 1) ^ 0x31u;
			}
			else
			{
				crc = (crc << 1);
			}
		}
	}
	return crc;
}

