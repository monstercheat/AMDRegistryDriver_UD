#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <iostream>

#include "registry.h"
#include "structs.h"

class Driver
{
private:
    static HANDLE  Mutex;
    static PBOOLEAN Running;
    static CRegistry* Registry;
    static INT32   ProcessID;
    static ULONG64 BaseAddress;
    static ULONG64 ProcessCR3;
public:
    static BOOLEAN DeviceCall(ULONG Instruction, PVOID Buffer, size_t SizeOfBuffer);
    static BOOLEAN AttachToProcess(LPCTSTR ProcessName);
    static BOOLEAN ReadMemory(ULONG64 Address, PVOID Destination, size_t NumberOfBytes);
    static BOOLEAN WriteMemory(ULONG64 Address, PVOID Source, size_t NumberOfBytes);
    static BOOLEAN Load(PBOOLEAN RunningContext);
    static BOOLEAN Unload();
    static INT32 FindProcessID(LPCTSTR ProcessName);
    static INT32 getProcessID();
    static ULONG64 getBaseAddress();
};

template<typename T>
T read(ULONG64 Address)
{
    T Result;
    SecureZeroMemory(&Result, sizeof(Result));
    Driver::ReadMemory(Address, &Result, sizeof(Result));
    return Result;
}
template<typename T>
VOID write(ULONG64 Address, T Source)
{
    Driver::WriteMemory(Address, &Source, sizeof(Source));
}