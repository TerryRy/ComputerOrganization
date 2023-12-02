/*
 * uart.c
 *
 * created: 2021/8/26
 *  author:
 */

#include "bsp.h"

#include <string.h>

#if defined(LS1C)
#include "ls1c_gpio.h"
#endif

#include "ns16550.h"

//-------------------------------------------------------------------------------------------------

static char s1[] = "hello world!";
static char s2[] = "Jerry.";
static char s3[] = "What is Tom doing?";
static char s4[] = "repeat";

//-------------------------------------------------------------------------------------------------
// 接收与发送函数
//-------------------------------------------------------------------------------------------------

static int send_string(const char *str)
{
    int len;
    len = strlen(str);
    ls1x_uart_write(devUART3, str, len, NULL);
    printk("TX: %s\r\n", str);                          // 打印耗时==延时
    return len;
}


static int receive_string(char *re_buf)
{
    //receive主机发送的字符串，写入缓冲区，缓冲区是一个队（先进先出），每都会弹出缓冲区的前size个字符进行返回
    int count;
    int size = 12;
    char buf[64]= {""};
    count = ls1x_uart_read(devUART3, buf, size, 30);
    if (count == 0)
    {
        return -1;
    }
    memcpy(re_buf,buf,strlen(buf));
    return count;
}
//-------------------------------------------------------------------------------------------------
// 主机
//-------------------------------------------------------------------------------------------------

static int uart3_opened = 0;

void uart3_master_work(void)
{
    char str[50] = {""};
    if (!uart3_opened)
    {
        // Set device UART3
        ls1x_uart_init(devUART3, NULL);     // default: 115200, 8N1
        ls1x_uart_open(devUART3, NULL);
        uart3_opened = 1;
    }
    
    send_string(s1);              /* 发送 s1 */
    delay_ms(1000);
    if (receive_string(str) < 0)       /* 接收 s2 */
    {
        return;
    }
    send_string(str);
    delay_ms(1000);
    send_string("master done");
}

//-------------------------------------------------------------------------------------------------
// 从机，无需了解
//-------------------------------------------------------------------------------------------------

static int slave_count = 0;

void uart3_slave_work(void)
{
    if (!uart3_opened)
    {
        /*
         * Set device UART3
         */
        ls1x_uart_init(devUART3, NULL);     // default: 115200, 8N1
        ls1x_uart_open(devUART3, NULL);
        uart3_opened = 1;
    }

    send_string(s2);              /* 发送 s2 */
    send_string(s4);              /* 发送 s4 */

    slave_count++;
    printk("slave done, %i...\r\n\r\n", slave_count);

    delay_ms(50);
}


