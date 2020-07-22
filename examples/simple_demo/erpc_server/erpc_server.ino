#include <Seeed_Arduino_FreeRTOS.h>
#include "erpc_server_setup.h"
#include "erpc_setup_arduino_uart.h"
#include "erpc_demo_server.h"
TaskHandle_t app_task_handle = NULL;
#define APP_TASK_STACK_SIZE 512

void app_task(void *param)
{
    auto transport = erpc_transport_uart_init(&Serial1);
    /* init eRPC server environment */
    /* MessageBufferFactory initialization */
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    /* eRPC server side initialization */
    erpc_server_init(transport, message_buffer_factory);
    /* connect generated service into server, look into erpcdemo_server.h */
    erpc_add_service_to_server(create_DEMO_service());
    Serial.println("start erpcdemo server");
    /* run server */
    while (1)
    {
        /* process message */
        erpc_server_poll();
    }

    /* close uart */
    erpc_transport_uart_deinit();

    vTaskDelete(NULL);
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    };

    int result = xTaskCreate(app_task, "TEST_TASK", APP_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &app_task_handle);

    vTaskStartScheduler();
}

void loop()
{
}