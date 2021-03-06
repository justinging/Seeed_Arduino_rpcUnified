/*
 * Copyright (c) 2020 SeeedStudio.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "erpc_arduino_uart_transport.h"

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

UartTransport::UartTransport(HardwareSerial *uartDrv, unsigned long baudrate)
    : m_uartDrv(uartDrv), m_baudrate(baudrate)
{
}

UartTransport::~UartTransport(void)
{
}

erpc_status_t UartTransport::init(void)
{

    m_uartDrv->begin(m_baudrate);
    return kErpcStatus_Success;
}

erpc_status_t UartTransport::underlyingReceive(uint8_t *data, uint32_t size)
{
    uint32_t bytesRead = 0;
    uint8_t *temp = data;
    while (bytesRead < size)
    {
        while (m_uartDrv->available())
        {
            int c =  m_uartDrv->read();
            if (c < 0)
                break;
            *data++ = (char)c;
            bytesRead++;
            if(bytesRead == size)
                break;
        }
        delay(10);
    }
    // Serial.printf("underlyingReceive: size %d\n\rdata:\n\r", size);
    // for(int i = 0; i < bytesRead; i++)
    // {
    //     Serial.printf("0x%02x ", temp[i]);
    //     if(i % 9 == 0 && i != 0)
    //     {
    //         Serial.printf("\n\r");
    //     }
    // }
    // Serial.printf("\n\r");
    return size != bytesRead ? kErpcStatus_ReceiveFailed : kErpcStatus_Success;
}

erpc_status_t UartTransport::underlyingSend(const uint8_t *data, uint32_t size)
{
    uint32_t bytesRead = size;
    const uint8_t *temp = data;
    // Serial.printf("underlyingSend: size %d\n\rdata:\n\r");
    // for(int i = 0; i < bytesRead; i++)
    // {
    //     Serial.printf("0x%02x ", temp[i]);
    //     if(i % 9 == 0 && i != 0)
    //     {
    //         Serial.printf("\n\r");
    //     }
    // }
    // Serial.printf("\n\r");

    uint32_t bytesWritten = m_uartDrv->write(data, size);
    return size != bytesWritten ? kErpcStatus_SendFailed : kErpcStatus_Success;
}

bool UartTransport::hasMessage()
{
    if (m_uartDrv->available())
    {
        return true;
    }
    return false;
}
