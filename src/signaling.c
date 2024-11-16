#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include "signaling.h"

void calc_thread(void *args) {
    SemaphoreHandle_t request = xSemaphoreCreateCounting(1, 0);
    SemaphoreHandle_t response = xSemaphoreCreateCounting(1, 0);
    struct signal_data sig_data= {10, 0};
    //struct task_args task_args = {request, response, &sig_data};

    while(1) {
        signal_handle_calculation(request, response, &sig_data);
    }
}
// This is the worker thread. Waits for a request, increments data by 5, and signals
// the request thread that request has been filled.
void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response,
                               struct signal_data *data) {
    // Wait for a request to come in
    xSemaphoreTake(request, portMAX_DELAY);
    data->output = data->input + 5;
    xSemaphoreGive(response);
}

// This is the request thread. Sends out a request for calculation and returns the status
// of the request.
BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response,
                                    struct signal_data *data) {
    xSemaphoreGive(request);
    return xSemaphoreTake(response, 500);
}