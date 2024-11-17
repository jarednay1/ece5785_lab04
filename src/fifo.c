#include <stdio.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "fifo.h"
#include "signaling.h"

void handler_task(void *vargs)
{
    struct task_args *args = (struct task_args *)vargs;
    fifo_worker_handler(args->request, args->response, args->id);
}

