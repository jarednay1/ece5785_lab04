/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "signaling.h"


int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t master;
    sleep_ms(10000);
    printf("made it after sleep\n");
    xTaskCreate(master_task, "MasterTask", MASTER_TASK_STACK_SIZE, NULL,
                MASTER_TASK_PRIORITY, &master);
    vTaskStartScheduler();
    return 0;
}
