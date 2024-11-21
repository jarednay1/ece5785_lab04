#pragma once

#include <FreeRTOS.h>
#include <queue.h>

#define WORKER_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define WORKER_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define MASTER_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define MASTER_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

#define THREAD_COUNT 4

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

extern int setup_pool;

extern TaskHandle_t worker_threads[THREAD_COUNT];
extern struct task_args worker_args[THREAD_COUNT];
extern QueueHandle_t request;
extern QueueHandle_t response;

void fifo_master_task(void *args);
void handler_task(void *vargs);
void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id);
void run_fifo_task(void);
void setUp(void);
void tearDown(void);