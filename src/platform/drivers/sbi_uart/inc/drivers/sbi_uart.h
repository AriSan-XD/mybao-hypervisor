/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __SBI_UART_H__
#define __SBI_UART_H__

#include <bao.h>

typedef volatile uint8_t bao_uart_t;

bool uart_init(bao_uart_t* uart);
void uart_enable(bao_uart_t* uart);
void uart_putc(bao_uart_t* uart, const int8_t c);

#endif /* __SBI_UART_H__ */
