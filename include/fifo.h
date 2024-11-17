#pragma once
#include <FreeRTOS.h>
#include <queue.h>

#define WORKER_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define WORKER_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define MASTER_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define MASTER_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

struct request_msg {
    int32_t input;
    int32_t output;
    uint32_t handled_by;
};

struct task_args
{
    QueueHandle_t request;
    QueueHandle_t response;
    int id;
};

void fifo_master_handler(void *args);
void handler_task(void *vargs);
void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id);