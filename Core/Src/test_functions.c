/*
 * test_functions.c
 *
 *  Created on: 14 set 2026
 *      Author: jacop
 */
#include "test_functions.h"
#include "usart.h"
#include "i2c.h"
#include "main.h"
#include <stdio.h>


static uint8_t CalcCrcSGP40(uint8_t data[2]);


void TestUart1()
{
	const uint8_t tx_buf[5] = {0x00, 0x01, 0x02, 0x03, 0x04};

	// Mi aspetto 5 numeri trasmessi -> OK
	//HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, &tx_buf[0], sizeof(tx_buf), 500);

}


void TestI2C()
{
//	uint8_t tx_buff = 0x03;
//
//	// Da verificare con oscilloscopio. Non è test dei sensori. -> OK
//	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, 0x01<<1, 0x01, 0x01/*in byte*/, &tx_buff, sizeof(tx_buff), 500);
}


void TestSGP40()
{
	const char* TAG = "SGP40_Test";

	const uint8_t dev_address = 0x59;
	uint8_t tx_buff[2] = {0x36, 0x82};
	uint8_t rx_buff[9] = {0};

	// Leggo il serial number. Timeout max 2ms
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, dev_address<<1, &tx_buff[0], 2, 500);
	status = HAL_I2C_Master_Receive(&hi2c1, dev_address<<1, &rx_buff[0], sizeof(rx_buff), 2);

	// -> ok
	uint8_t crc_byte_1_2 = CalcCrcSGP40(&rx_buff[0]);
	uint8_t crc_byte_3_4 = CalcCrcSGP40(&rx_buff[3]);
	uint8_t crc_byte_5_6 = CalcCrcSGP40(&rx_buff[6]);

	// fare assert per debug su seriale
	printf("%s: ser_numer byte 1-2 CRC [expected / received]: [0x%02X / 0x%02X]\n", TAG, rx_buff[2], crc_byte_1_2);
	printf("%s: ser_numer byte 3-4 CRC [expected / received]: [0x%02X / 0x%02X]\n", TAG, rx_buff[5], crc_byte_3_4);
	printf("%s: ser_numer byte 5-6 CRC [expected / received]: [0x%02X / 0x%02X]\n\n", TAG, rx_buff[8], crc_byte_5_6);
}


void TestSHT40_AD1B()
{
	// Da datasheet i possibili per il nostro modello sono: 0x44, 0x45, 0x46
	const uint8_t dev_address = 0x44;

	uint8_t tx_buff[1] = {0x89};
	uint8_t rx_buff[6] = {0};

	// Leggo il serial number. Timeout max 2ms
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, dev_address<<1, &tx_buff[0], 1, 500);
	status = HAL_I2C_Master_Receive(&hi2c1, dev_address<<1, &rx_buff[0], sizeof(rx_buff), 500);

	// CRC uguale al SGP40 -> ok
	uint8_t crc_byte_1_2 = CalcCrcSGP40(&rx_buff[0]);
	uint8_t crc_byte_3_4 = CalcCrcSGP40(&rx_buff[3]);
}


void TestButton()
{
	const char* TAG = "Button_Test";

	// Il pulsante è collegato alla linea EXTI3
	uint8_t local_cnt = button_cnt;
	printf("%s: button_cnt : %d\n", TAG, local_cnt);
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

