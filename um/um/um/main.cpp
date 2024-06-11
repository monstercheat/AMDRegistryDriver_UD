#include <Windows.h>
#include <TlHelp32.h>
#include <memory>
#include <string_view>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <dwmapi.h>
#include <random>
#include <winternl.h>
#include "thread"
#include <map>
#include <stack>
#include <atomic>
#include <array>
#include <cstring>
#include <unordered_map>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include <stack>
#include <fstream>
#include "driver/driver.h"

bool IsKeyDown(int vk)
{
	return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

int main()
{
	BOOLEAN Running;
	Running = TRUE;
	BOOLEAN* Runnin = &Running;

	if (!Driver::Load(Runnin))
	{
		MessageBox(GetForegroundWindow(),
			(L"Error! Driver not Initializing."), 0, MB_OK | MB_TOPMOST);
		ExitProcess(5);
	}

	if (!Driver::AttachToProcess(L"r5apex.exe"))
	{
		MessageBox(GetForegroundWindow(),
			(L"Error! Failed to Attaching Process."),
			(L"System Error"),
			MB_OK | MB_TOPMOST);
		Driver::Unload();
		ExitProcess(5);
	}

	std::cout << "ProcessID: " << Driver::getProcessID() << std::endl;
	std::cout << "BaseAddress: " << Driver::getBaseAddress() << std::endl;

	while (true) {

	}
}