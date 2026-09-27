/**
  ******************************************************************************
  * @file    tests_config.h
  * @brief   Defines to enable specific tests.
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
#ifndef INC_TESTS_CONFIG_H_
#define INC_TESTS_CONFIG_H_


/**
 * @brief Defines to enable / disable tests
 *
 * Set to 1 to enable test, 0 to disable.
 * For specific behaviour, see test_functions.c
 */
#define TEST_UART		0
#define TEST_I2C		0
#define TEST_SGP40		1
#define TEST_SHT40		1
#define TEST_BTN		1
#define TEST_DISPLAY	1

#endif /* INC_TESTS_CONFIG_H_ */
