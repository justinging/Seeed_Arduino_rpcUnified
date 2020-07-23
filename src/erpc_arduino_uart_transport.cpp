/*
 * Copyright (c) 2020 SeeedStudio.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "erpc_arduino_uart_transport.h"
#include <cstdio>

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

UartTransport::UartTransport(Uart *uartDrv, unsigned long baudrate, uint16_t config)
    : m_uartDrv(uartDrv), m_baudrate(baudrate), m_config(config)
{
}

UartTransport::~UartTransport(void)
{
}

erpc_status_t UartTransport::init(void)
{

    m_uartDrv->begin(115200);
    return kErpcStatus_Success;
}

erpc_status_t UartTransport::underlyingReceive(uint8_t *data, uint32_t size)
{
    size_t bytesRead = 0;
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
    return size != bytesRead ? kErpcStatus_ReceiveFailed : kErpcStatus_Success;
}

erpc_status_t UartTransport::underlyingSend(const uint8_t *data, uint32_t size)
{
    int32_t bytesWritten = m_uartDrv->write(data, size);
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
