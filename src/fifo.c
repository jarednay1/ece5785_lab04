#include <stdio.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "fifo.h"
#include "signaling.h"

// int setup_pool;

// TaskHandle_t worker_threads[THREAD_COUNT];
// struct task_args worker_args[THREAD_COUNT];
// QueueHandle_t request;
// QueueHandle_t response;

// Wrapper for worker task to be called. Was included in Ashton's test solution
// So I'ma keep it
void handler_task(void *vargs) {
    struct task_args *args = (struct task_args *)vargs;
    fifo_worker_handler(args->request, args->response, args->id);
}

// Master task, commented out for now cause I don't know how to only build
// one executable at a time.
// void fifo_master_task(void *args) {
//     struct request_msg responses[THREAD_COUNT]; 
//     int count = 0;
//     setup_pool = 1;
//     setUp();
//     run_fifo_task();

//     while (1) {
//         if (xQueueReceive(response, (&responses + count), portMAX_DELAY)) {
//             printf("Output: %d\n", responses[count].output);
//         }

//         // Kill the master
//         if (!setup_pool) {
//             vTaskDelete(NULL);
//         }
//     }
// }

// Workers wait here to receive a message
void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id) {
    struct request_msg msg = {};
    while(1) {
        if (xQueueReceive(requests, &msg, portMAX_DELAY)) {
            msg.output = msg.input + 5;
            msg.handled_by = id;
            xQueueSend(results, &msg, portMAX_DELAY);
        }
    }
}

// Helper for master thread to create inputs
void run_fifo_task(void) {
    for (int i = 0; i < 4; i++) {
        struct request_msg msg = {};
        msg.input = i;
        xQueueSendToBack(request, &msg, portMAX_DELAY);
    }
}

// Set up worker threads
void setUp(void)
{
    request = xQueueCreate(100, sizeof(struct request_msg));
    response = xQueueCreate(100, sizeof(struct request_msg));

    if (setup_pool) {
        for (int t = 0; t < THREAD_COUNT; t++) {
            struct task_args arg = {request, response, t};
            worker_args[t] = arg;
            xTaskCreate(handler_task,
                        "worker",
                        WORKER_TASK_STACK_SIZE,
                        (void *)(worker_args + t),
                        WORKER_TASK_PRIORITY,
                        worker_threads + t);
        }
    }
}

// Delete all workers
void tearDown(void)
{
    if (setup_pool) {
        for (int t = 0; t < THREAD_COUNT; t++) {
            vTaskDelete(worker_threads[t]);
        }
    }
    vQueueDelete(request);
    vQueueDelete(response);
}

