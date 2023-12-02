/*
 * uart.h
 *
 * created: 2021/8/26
 *  author:
 */

#ifndef _UART_H
#define _UART_H


#endif // _UART_H


static int send_string(char protocol, const char *str);
static int receive_string(char protocol);
void uart3_master_work(void);
void uart3_slave_work(void);
//static int receive_string(char protocol, char *str);

