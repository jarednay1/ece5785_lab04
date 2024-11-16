#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include "signaling.h"

void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response,
                               struct signal_data *data);

// Should be 32 bit?
BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response,
                                    struct signal_data *data);