#include <Windows.h>
#include <WinBase.h>
#include <iostream>

size_t getTotalSystemMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys;
}

int main() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo( &sysinfo );

    std::cout << "Total Cores: " << sysinfo.dwNumberOfProcessors << std::endl;
    std::cout << "Total Memory: " << getTotalSystemMemory() << std::endl;
    return 0;
}

