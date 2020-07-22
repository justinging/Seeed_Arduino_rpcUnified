#include <Seeed_Arduino_FreeRTOS.h>
#include "erpc_client_setup.h"
#include "erpc_setup_arduino_uart.h"
#include "erpc_port.h"
#include "erpc_demo.h"
TaskHandle_t app_task_handle = NULL;
#define APP_TASK_STACK_SIZE 512
// Free space allocated inside struct binary_t function implementation
static void free_binary_t_struct(binary_t *data)
{
	if (data->data)
	{
		erpc_free(data->data);
	}
	erpc_free(data);
}
void app_task(void *param)
{

	auto transport = erpc_transport_uart_init(&Serial1);
	delay(100);
	/* init eRPC server environment */
	/* MessageBufferFactory initialization */
	erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
	/* eRPC server side initialization */
	erpc_client_init(transport, message_buffer_factory);

	auto msg = "hello!!!!!";
	binary_t b = {(uint8_t *)msg, (uint32_t)strlen(msg)};
	while (1)
	{
		{
			/* RPC call */
			auto resp = RD_demoHello1(&b);
			/* print return value */
			Serial.printf("RD_demoHello1 :%s\n\r", resp->data);

			free_binary_t_struct(resp);
		}
		{
			binary_t r;
			auto code = RD_demoHello2(&b, &r);
			if (code == lErrorOk_c)
			{
				/* print return value */
				Serial.printf("RD_demoHello2 :%s\n\r", r.data);
				erpc_free(r.data);
			}
			else
			{
				Serial.printf("RD_demoHello2 response ERROR: %d\n\r", code);
			}
		}
		{
			int8_t out[256];
			int32_t size;
			auto code = RD_demoHello3(&b, out, &size);
			if (code == lErrorOk_c)
			{
				/* print return value */
				Serial.printf("RD_demoHello3 :%s\n\r", out);
			}
			else
			{
				Serial.printf("RD_demoHello3 response ERROR: %d\n\r", code);
			}
		}
		delay(5000);
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
	delay(1000);
	int result = xTaskCreate(app_task, "TEST_TASK", 1024, NULL, tskIDLE_PRIORITY + 1, &app_task_handle);

	vTaskStartScheduler();
}
void loop()
{
	Serial.println(1);
}
