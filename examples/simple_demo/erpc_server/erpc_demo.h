/* Define the project name, which is also the prefix of all generated source code file names*/

/*
 * Generated by erpcgen 1.7.3 on Wed Jul 22 15:48:27 2020.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#if !defined(_erpc_demo_h_)
#define _erpc_demo_h_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "erpc_version.h"

#if 10703 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif

#if !defined(ERPC_TYPE_DEFINITIONS)
#define ERPC_TYPE_DEFINITIONS

// Enumerators data types declarations
/*! Define return state enume */
typedef enum lockErrors_t
{
    lErrorOk_c = 0,
    lErrorOutofMemory_c = 1,
    lErrorMaxError_c = 2
} lockErrors_t;

// Aliases data types declarations
typedef struct binary_t binary_t;

// Structures/unions data types declarations
struct binary_t
{
    uint8_t * data;
    uint32_t dataLength;
};


#endif // ERPC_TYPE_DEFINITIONS

/*! @brief DEMO identifiers */
enum _DEMO_ids
{
    kDEMO_service_id = 1,
    kDEMO_RD_demoHello1_id = 1,
    kDEMO_RD_demoHello2_id = 2,
    kDEMO_RD_demoHello3_id = 3,
};

#if defined(__cplusplus)
extern "C" {
#endif

/*! Define service interface functions, */
//! @name DEMO
//@{
binary_t * RD_demoHello1(const binary_t * txInput);

lockErrors_t RD_demoHello2(const binary_t * txInput, binary_t * txOutput);

lockErrors_t RD_demoHello3(const binary_t * txInput, int8_t txOutput[64], int32_t * size);
//@}

#if defined(__cplusplus)
}
#endif

#endif // _erpc_demo_h_
