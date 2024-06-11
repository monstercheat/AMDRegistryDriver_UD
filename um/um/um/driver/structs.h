#pragma once

#define REGISTRY_PATH_KERNEL			L"\\Registry\\Machine\\SYSTEM\\ControlSet001\\Control"
#define REGISTRY_PATH_CLIENT            L"SYSTEM\\ControlSet001\\Control"

#define ALLOC_POOL_TAG                  ' KRS'

#define REQUEST_RUNNING_STATUS          ' RUN'
#define REQUEST_PROCESS_ADDRESS         ' RPA'
#define REQUEST_READ_MEMORY             ' RPM'
#define REQUEST_WRITE_MEMORY            ' WPM'
#define REQUEST_MOUSE_MOVE              ' MOU'

#define STATUS_REQUEST_ACTIVE           'ACTV'
#define STATUS_REQUEST_WORKING          'WORK'
#define STATUS_REQUEST_COMPLETED        'DONE'


typedef struct _KERNEL_REQUEST {

    ULONG   Instruction;
    PVOID   Buffer;
    SIZE_T  NumberOfBytes;

} KERNEL_REQUEST, * PKERNEL_REQUEST;

typedef struct _PROCESS_ADDRESS_REQUEST {

    ULONG   ProcessId;
    ULONG64 BaseAddress;
    ULONG64 ProcessCR3;

} PROCESS_ADDRESS_REQUEST, * PPROCESS_ADDRESS_REQUEST;

typedef struct _COPY_MEMORY_REQUEST {

    ULONG64 ProcessCR3;
    PVOID   Source;
    PVOID   Destination;
    SIZE_T  NumberOfBytes;

} COPY_MEMORY_REQUEST, * PCOPY_MEMORY_REQUEST;