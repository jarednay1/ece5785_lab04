# # #FIFO TESTING
add_executable(lab4_test_fifo 
  test_fifo.c 
  ../src/fifo.c 
  unity_config.c)
target_link_libraries(lab4_test_fifo PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  pico_cyw43_arch_none
  unity
)
pico_enable_stdio_uart(lab4_test_fifo 0)
pico_enable_stdio_usb(lab4_test_fifo 1)
add_custom_target(flash_test_
    picotool load -f $<TARGET_FILE:lab4_test_fifo> DEPENDS lab4_test_fifo)

    if(PICO_CYW43_SUPPORTED)
    target_link_libraries(lab4_test_fifo PRIVATE
        pico_cyw43_arch_none
    )
endif()

# SIGNAL TESTING
# add_executable(lab4_test_signal 
#   test_signal.c 
#   ../src/signaling.c 
#   unity_config.c)

# target_link_libraries(lab4_test_signal PRIVATE
#   pico_stdlib
#   pico_async_context_freertos
#   FreeRTOS-Kernel-Heap4
#   pico_cyw43_arch_none
#   unity
# )
# pico_enable_stdio_uart(lab4_test_signal 0)
# pico_enable_stdio_usb(lab4_test_signal 1)
# add_custom_target(flash_test_signal 
#     picotool load -f $<TARGET_FILE:lab4_test_signal> DEPENDS lab4_test_signal)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
# if(PICO_CYW43_SUPPORTED)
#     target_link_libraries(lab4_test_signal PRIVATE
#         pico_cyw43_arch_none
#     )
# endif()


