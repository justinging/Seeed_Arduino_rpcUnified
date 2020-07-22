/*
 * sample_demo_server_impl.cpp
 * erpcdemo RPC implementation
 * Created on: Jul 22, 2020
 * Author: Hongtai.liu(hongtai.liu@seeed.cc)
 */

#include "erpc_demo_server.h"
#include "erpc_port.h"
#include "Arduino.h"
using namespace std;
/** retrun hi while call this function */

binary_t *RD_demoHello1(const binary_t *txInput)
{
    Serial.printf("RD_demoHello1 Called \n\r");
    Serial.printf("receive: %s\n\r", (char*)txInput->data);
    auto msg = "hi!";
    auto length = strlen(msg) + 1;

    binary_t *result = NULL;
    char* buf = NULL;

    buf = (char *) erpc_malloc(length * sizeof(char));
    strncpy(buf, msg, length);

    result = (binary_t *) erpc_malloc(sizeof(binary_t));
	result->dataLength = length;
	result->data = (uint8_t *)buf;
	return result;
}

/** retrun error code while call this function, and fill txOutput*/
lockErrors_t RD_demoHello2(const binary_t *txInput, binary_t *txOutput)
{
    Serial.printf("RD_demoHello2 Called \n\r");
    Serial.printf("receive: %s\n\r", (char*)txInput->data);
    auto msg = "hi!";
    auto length = strlen(msg) + 1;

    binary_t *result = NULL;
    char *buf = NULL;

    buf = (char *) erpc_malloc(length * sizeof(char));
    strncpy(buf, msg, length);

    result = (binary_t *) erpc_malloc(sizeof(binary_t));
	txOutput->dataLength = length;
	txOutput->data = (uint8_t *)buf;
	return lErrorOk_c;
}
lockErrors_t RD_demoHello3(const binary_t *txInput, int8_t txOutput[64], int32_t *size)
{
    Serial.printf("RD_demoHello3 Called \n\r");
    Serial.printf("receive: %s\n\r", (char*)txInput->data);
    auto msg = "hi!";
    auto length = strlen(msg) + 1;

    binary_t *result = NULL;
    char *buf = NULL;

    buf = (char *) erpc_malloc(length * sizeof(char));
    strncpy(buf, msg, length);

    result = (binary_t *) erpc_malloc(sizeof(binary_t));
	*size = length;
	strncpy((char*)txOutput, buf, 64);
	return lErrorOk_c;
}
