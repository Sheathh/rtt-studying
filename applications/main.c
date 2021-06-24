/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-23     RT-Thread    first version
 */

#include <rtthread.h>
#include<drv_soft_i2c.h>
#include<arpa/inet.h>
#include<netdev.h>
#include<ntp.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

int sh31_ccollcet(void);

int main(void)
{
    LOG_D("HELLO!");
    //获取网卡对象
    struct netdev* net = netdev_get_by_name("esp0");
    //阻塞判断当前网络是否正常连接
    while(netdev_is_internet_up(net) != 1)
    {
       rt_thread_mdelay(200);
    }
    //提示当前网络已就绪
                                                        //rt_kprintf("network is ok!\n");
    //NTP自动对时
    time_t cur_time;
    cur_time = ntp_sync_to_rtc(NULL);
    if (cur_time)
    {
        rt_kprintf("Cur Time: %s", ctime((const time_t*) &cur_time));
    }
    else
    {
        rt_kprintf("NTP sync fail.\n");
    }


    return RT_EOK;
}
