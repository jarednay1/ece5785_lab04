#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include "signaling.h"

// Master thread
void master_task(void *args) {
    run_task();

    while(1) {}
}

void run_task(void) {
    SemaphoreHandle_t request = xSemaphoreCreateCounting(1, 0);
    SemaphoreHandle_t response = xSemaphoreCreateCounting(1, 0);
    TaskHandle_t calc;
    struct signal_data sig_data = {0, 0}; 
    struct calc_task_args task_args = {request, response, &sig_data};
    int status;

    xTaskCreate(calc_task, "CalcTask", WORKER_TASK_STACK_SIZE, (void *) &task_args, 
                WORKER_TASK_PRIORITY, &calc);

    for (int i = 0; i < 3; i++) {
        vTaskDelay(1000);
        task_args.data->input = i;
        status = signal_request_calculate(request, response, &sig_data);
        printf("status: %d\n", status);
        printf("output: %d\n", sig_data.output);

    }
    vTaskDelete(calc);
}

void calc_task(void *vargs) {
    struct calc_task_args *task_args = (struct calc_task_args *)vargs;
    // Task loop
    while(1) {
        signal_handle_calculation(task_args->request, task_args->response, 
                                    task_args->data);
    }
}
// This is the worker thread. Waits for a request, increments data by 5, and signals
// the request thread that request has been filled.
void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response,
                               struct signal_data *data) {
    // Wait for a request to come in
    printf("Waiting for request\n");
    xSemaphoreTake(request, portMAX_DELAY);
    data->output = data->input + 5;
    printf("Data calculated\n");
    xSemaphoreGive(response);
}

// This is the request thread. Sends out a request for calculation and returns the status
// of the request.
BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response,
                                    struct signal_data *data) {
    int status;
    printf("Requesting a calculation\n");
    xSemaphoreGive(request);
    printf("Requested\n");
    status = xSemaphoreTake(response, 500);
    printf("Response recieved\n");
    return status;
}