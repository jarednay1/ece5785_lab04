#pragma once

#include <FreeRTOS.h>
#include <semphr.h>

#define MASTER_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define MASTER_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define MASTER_RUNNER_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define MASTER_RUNNER_STACK_SIZE configMINIMAL_STACK_SIZE

struct signal_data {
    int32_t input;
    int32_t output;
};

struct task_args {
    SemaphoreHandle_t request;
    SemaphoreHandle_t response;
    struct signal_data *data;
};

// Master thread
void master_task(void *args);

// Calc task to perform the calculation
void calc_task(void *args);

// Worker thread
void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response,
                               struct signal_data *data);

// Request to use worker thread
BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response,
                                    struct signal_data *data);