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
#include "fifo.h"


int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t signal_master, fifo_master;
    sleep_ms(10000);
    printf("made it after sleep\n");
    hard_assert(cyw43_arch_init() == PICO_OK);

    // -----This runs signaling-----
    xTaskCreate(master_task, "MasterTask", MASTER_TASK_STACK_SIZE, NULL,
                 MASTER_TASK_PRIORITY, &signal_master);

    // -----This runs fifo------
    // xTaskCreate(fifo_master_task, "FifoMasterTask", MASTER_TASK_STACK_SIZE, NULL,
    //              MASTER_TASK_PRIORITY, &fifo_master);

    vTaskStartScheduler();
    run_task();
    return 0;
}
