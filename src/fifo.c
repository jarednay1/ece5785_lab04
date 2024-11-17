#include <stdio.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "fifo.h"
#include "signaling.h"

void handler_task(void *vargs) {
    struct task_args *args = (struct task_args *)vargs;
    fifo_worker_handler(args->request, args->response, args->id);
}

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

