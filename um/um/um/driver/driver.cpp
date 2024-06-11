#include "driver.h"

HANDLE Driver::Mutex;
PBOOLEAN Driver::Running;
CRegistry* Driver::Registry;
INT32 Driver::ProcessID;
ULONG64 Driver::BaseAddress;
ULONG64 Driver::ProcessCR3;

BOOLEAN Driver::DeviceCall(ULONG Instruction, PVOID Buffer, size_t SizeOfBuffer)
{
    ULONG dwWaitResult;
    KERNEL_REQUEST Request;
    ULONG64 Timer;

    SecureZeroMemory(&Request, sizeof(Request));
    Request.Instruction = Instruction;
    Request.Buffer = Buffer;
    Request.NumberOfBytes = SizeOfBuffer;

    dwWaitResult = WaitForSingleObject(Mutex,      // handle to mutex
        INFINITE);  // no time-out interval

    switch (dwWaitResult)
    {
        // The thread got ownership of the mutex
    case WAIT_OBJECT_0:
        __try {

            Registry->DeleteValue(("Client ID"));
            Registry->DeleteValue(("Address"));

            Registry->WriteDWORD(("Client ID"), GetCurrentProcessId());
            Registry->WriteDWORD64(("Address"), reinterpret_cast<ULONG64>(&Request));

            Registry->WriteDWORD(("Status"), STATUS_REQUEST_WORKING);             // Set Working

            Timer = GetTickCount64();
            while (Registry->ReadDWORD(("Status")) != STATUS_REQUEST_COMPLETED && // Once it done,
                *Running == TRUE && (GetTickCount64() - Timer) < 2000);         // Max Wait Time 2 second
            Registry->WriteDWORD(("Status"), STATUS_REQUEST_ACTIVE);              // Set To Idle
        }
        __finally {
            // Release ownership of the mutex object
            if (!ReleaseMutex(Mutex))
            {
                Registry->DeleteValue(("Client ID"));
                Registry->DeleteValue(("Address"));
                Registry->DeleteValue(("Status"));

                MessageBox(
                    GetForegroundWindow(),
                    (L"Mutex ownership error!"), 0, MB_OK | MB_TOPMOST);
                return FALSE;
            }
        }
        break;

    case WAIT_ABANDONED:
        MessageBox(
            GetForegroundWindow(),
            (L"Mutex Abandoned error!"), 0, MB_OK | MB_TOPMOST);
        return FALSE;
        break;
    }

    return TRUE;
}

BOOLEAN Driver::AttachToProcess(LPCTSTR ProcessName)
{
    PROCESS_ADDRESS_REQUEST Request;
    BOOLEAN Result;

    Request.ProcessId = FindProcessID(ProcessName);
    Request.BaseAddress = 0;
    Request.ProcessCR3 = 0;
    Result = DeviceCall(REQUEST_PROCESS_ADDRESS, &Request, sizeof(Request));
    ProcessID = Request.ProcessId;
    BaseAddress = Request.BaseAddress;
    ProcessCR3 = Request.ProcessCR3;

    return Result;
}

BOOLEAN Driver::Load(PBOOLEAN RunningContext)
{
    ProcessID = 0;
    BaseAddress = 0;
    ProcessCR3 = 0;
    Running = RunningContext;
    Registry = new CRegistry(HKEY_LOCAL_MACHINE, REGISTRY_PATH_CLIENT);

    Mutex = CreateMutex(NULL, FALSE, NULL);
    if (Mutex == NULL)
    {
        MessageBoxA(0, "Error! Failed to create device mutex.", 0, MB_OK | MB_TOPMOST);
        return FALSE;
    }

    Registry->DeleteValue(("Client ID"));
    Registry->DeleteValue(("Address"));
    Registry->WriteDWORD(("Status"), STATUS_REQUEST_ACTIVE);

    BOOLEAN Running;
    Running = FALSE;
    DeviceCall(REQUEST_RUNNING_STATUS, &Running, sizeof(Running));

    if (Running == FALSE)
        DeviceCall(REQUEST_RUNNING_STATUS, &Running, sizeof(Running));

    return Running;
}

BOOLEAN Driver::Unload()
{
    Registry->DeleteValue(("Client ID"));
    Registry->DeleteValue(("Address"));
    Registry->WriteDWORD(("Status"), STATUS_REQUEST_COMPLETED);
    Registry->~CRegistry();
    return CloseHandle(Mutex);
}

INT32 Driver::FindProcessID(LPCTSTR ProcessName)
{
    HANDLE hsnap;
    PROCESSENTRY32 pt;
    ULONG PiD;
    hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pt.dwSize = sizeof(PROCESSENTRY32);
    do {
        if (!_tcscmp(pt.szExeFile, ProcessName)) {
            CloseHandle(hsnap);
            PiD = pt.th32ProcessID;
            return PiD;
            if (PiD != NULL) {
                return 0;
            }
        }
    } while (Process32Next(hsnap, &pt));
    return 0;
}

BOOLEAN Driver::ReadMemory(ULONG64 Address, PVOID Destination, size_t NumberOfBytes)
{
    COPY_MEMORY_REQUEST Request;
    Request.ProcessCR3 = ProcessCR3;
    Request.Source = reinterpret_cast<PVOID>(Address);
    Request.Destination = Destination;
    Request.NumberOfBytes = NumberOfBytes;
    return DeviceCall(REQUEST_READ_MEMORY, &Request, sizeof(Request));
}

BOOLEAN Driver::WriteMemory(ULONG64 Address, PVOID Source, size_t NumberOfBytes)
{
    COPY_MEMORY_REQUEST Request;
    Request.ProcessCR3 = ProcessCR3;
    Request.Source = Source;
    Request.Destination = reinterpret_cast<PVOID>(Address);
    Request.NumberOfBytes = NumberOfBytes;
    return DeviceCall(REQUEST_WRITE_MEMORY, &Request, sizeof(Request));
}

INT32 Driver::getProcessID()
{
    return ProcessID;
}

ULONG64 Driver::getBaseAddress()
{
    return BaseAddress;
}