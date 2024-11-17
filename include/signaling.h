#pragma once

#include <FreeRTOS.h>
#include <semphr.h>

#define WORKER_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define WORKER_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define MASTER_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define MASTER_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

struct signal_data {
    int32_t input;
    int32_t output;
};

struct calc_task_args {
    SemaphoreHandle_t request;
    SemaphoreHandle_t response;
    struct signal_data *data;
};

// Master thread
void master_task(void *args);

// Run the task
void run_task(void);

// Calc task to perform the calculation
void calc_task(void *vargs);

// Do calculation when a request has come in
void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response,
                               struct signal_data *data);

// Request a calculation to be done. Returns the status of taking the semaphore.
BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response,
                                    struct signal_data *data);