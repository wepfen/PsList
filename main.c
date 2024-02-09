#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string.h>

void printHelp()
{
    printf("Usage: pslist.exe [flag]\n");
    printf("  -h  -> Show help message.\n");
    printf("  -d  -> Show thread detail.\n");
}

void listThreads(unsigned long processID)
{
    HANDLE threadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (threadSnap == INVALID_HANDLE_VALUE)
    {
        printf("Failed to snapshot.\n");
        return;
    }
    THREADENTRY32 te;
    te.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(threadSnap, &te))
    {
        do
        {   
            if (te.th32OwnerProcessID == processID)
            {
                printf("\nThread ID: %5d\n", te.th32ThreadID);
            }
        } while (Thread32Next(threadSnap, &te));
    }
    else
    {
        printf("Failed to get process.\n");
    }
    CloseHandle(threadSnap);
}

void listProcess(int processDetail)
{   
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        printf("Failed to snapshot.\n");
        return;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    printf("Name%43sPid%2sPri%2sThd \n\n"," ", " ", " ", " " );
    if (Process32First(snapshot, &pe))
    {
        do
        {   
            printf("%-45s%5d%5d%5d\n", pe.szExeFile, pe.th32ProcessID, pe.pcPriClassBase, pe.cntThreads);
            if (processDetail)
            {  
                listThreads(pe.th32ProcessID);
            }
        } while (Process32Next(snapshot, &pe));
    }
    else
    {
        printf("Failed to get process.\n");
    }
    CloseHandle(snapshot);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        listProcess(0);
    }
    else if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        printHelp();
    }
    else if (argc == 2 && strcmp(argv[1], "-d") == 0)
    {
        listProcess(1);
    }
    else
    {
        printHelp();
    }

    return 0;
}
