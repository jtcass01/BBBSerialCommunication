/*
 * uart.h
 *
 *  Created on: Nov 25, 2012
 *      Author: jaz
 */

#ifndef UART_H_
#define UART_H_

FILE 	*RX1_Handle = NULL, *TX1_Handle = NULL, *RX2_Handle = NULL, *TX2_Handle = NULL,
		*RX4_Handle = NULL, *TX4_Handle = NULL, *RX5_Handle = NULL, *TX5_Handle = NULL;

const char   *uart1_tx = "/sys/kernel/debug/omap_mux/uart1_txd",
			 *uart1_rx = "/sys/kernel/debug/omap_mux/uart1_rxd",
			 *uart2_tx = "/sys/kernel/debug/omap_mux/spi0_d0",
			 *uart2_rx = "/sys/kernel/debug/omap_mux/spi0_sclk",
			 *uart4_tx = "/sys/kernel/debug/omap_mux/gpmc_wpn",
			 *uart4_rx = "/sys/kernel/debug/omap_mux/gpmc_wait0",
			 *uart5_tx = "/sys/kernel/debug/omap_mux/lcd_data8",
			 *uart5_rx = "/sys/kernel/debug/omap_mux/lcd_data9";


#endif /* UART_H_ */