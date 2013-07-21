// ModAPIDll.cpp : Defines the exported functions for the DLL application.
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

#include "Executor.h"
#include "EntityHandler.h"

using namespace std;

Executor * executor;
EntityHandler * entityHandler;
typedef void (*f_Initialize)(Executor*);

void loadDllAndInitialize(string dll)	{
	LPCWSTR dllName = std::wstring(dll.begin(), dll.end()).c_str();
	HINSTANCE dllHandle = LoadLibrary(dllName);
	f_Initialize function = (f_Initialize) GetProcAddress(dllHandle, "Initialize");
	function(executor);
}

void Initialize(string list[])	{
	for (int i = 0; i < sizeof(list)/sizeof(*list); i++)	{
		loadDllAndInitialize(list[i]);
	}
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	executor = new Executor();
	//Patch executable
}


