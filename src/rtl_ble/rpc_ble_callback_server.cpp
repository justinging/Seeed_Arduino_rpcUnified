/*
 * Generated by erpcgen 1.7.4 on Thu Aug 20 10:51:20 2020.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#include "rpc_ble_callback_server.h"
#include <new>
#include "erpc_port.h"
#include "erpc_manually_constructed.h"

#if 10704 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif

using namespace erpc;
using namespace std;

#if ERPC_NESTED_CALLS_DETECTION
extern bool nestingDetection;
#endif

static ManuallyConstructed<rpc_ble_callback_service> s_rpc_ble_callback_service;


//! @brief Function to read struct binary_t
static void read_binary_t_struct(erpc::Codec * codec, binary_t * data);


// Read struct binary_t function implementation
static void read_binary_t_struct(erpc::Codec * codec, binary_t * data)
{
    uint8_t * data_local;
    codec->readBinary(&data->dataLength, &data_local);
    data->data = (uint8_t *) erpc_malloc(data->dataLength * sizeof(uint8_t));
    if (data->data == NULL)
    {
        codec->updateStatus(kErpcStatus_MemoryError);
    }
    else
    {
        memcpy(data->data, data_local, data->dataLength);
    }
}


//! @brief Function to free space allocated inside struct binary_t
static void free_binary_t_struct(binary_t * data);


// Free space allocated inside struct binary_t function implementation
static void free_binary_t_struct(binary_t * data)
{
    if (data->data)
    {
        erpc_free(data->data);
    }
}



// Call the correct server shim based on method unique ID.
erpc_status_t rpc_ble_callback_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory)
{
    switch (methodId)
    {
        case krpc_ble_callback_rpc_ble_handle_gap_msg_id:
            return rpc_ble_handle_gap_msg_shim(codec, messageFactory, sequence);

        case krpc_ble_callback_rpc_ble_gap_callback_id:
            return rpc_ble_gap_callback_shim(codec, messageFactory, sequence);

        default:
            return kErpcStatus_InvalidArgument;
    }
}

// Server shim for rpc_ble_handle_gap_msg of rpc_ble_callback interface.
erpc_status_t rpc_ble_callback_service::rpc_ble_handle_gap_msg_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;

    binary_t *gap_msg = NULL;
    gap_msg = (binary_t *) erpc_malloc(sizeof(binary_t));
    if (gap_msg == NULL)
    {
        codec->updateStatus(kErpcStatus_MemoryError);
    }

    // startReadMessage() was already called before this shim was invoked.

    read_binary_t_struct(codec, gap_msg);

    err = codec->getStatus();
    if (!err)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        rpc_ble_handle_gap_msg(gap_msg);
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (!err)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, krpc_ble_callback_service_id, krpc_ble_callback_rpc_ble_handle_gap_msg_id, sequence);

        err = codec->getStatus();
    }

    if (gap_msg)
    {
        free_binary_t_struct(gap_msg);
    }
    if (gap_msg)
    {
        erpc_free(gap_msg);
    }

    return err;
}

// Server shim for rpc_ble_gap_callback of rpc_ble_callback interface.
erpc_status_t rpc_ble_callback_service::rpc_ble_gap_callback_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;

    uint8_t cb_type;
    binary_t *cb_data = NULL;
    cb_data = (binary_t *) erpc_malloc(sizeof(binary_t));
    if (cb_data == NULL)
    {
        codec->updateStatus(kErpcStatus_MemoryError);
    }
    RPC_T_APP_RESULT result;

    // startReadMessage() was already called before this shim was invoked.

    codec->read(&cb_type);

    read_binary_t_struct(codec, cb_data);

    err = codec->getStatus();
    if (!err)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        result = rpc_ble_gap_callback(cb_type, cb_data);
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (!err)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, krpc_ble_callback_service_id, krpc_ble_callback_rpc_ble_gap_callback_id, sequence);

        codec->write(static_cast<int32_t>(result));

        err = codec->getStatus();
    }

    if (cb_data)
    {
        free_binary_t_struct(cb_data);
    }
    if (cb_data)
    {
        erpc_free(cb_data);
    }

    return err;
}

erpc_service_t create_rpc_ble_callback_service()
{
    s_rpc_ble_callback_service.construct();
    return s_rpc_ble_callback_service.get();
}

void destroy_rpc_ble_callback_service()
{
    s_rpc_ble_callback_service.destroy();
}