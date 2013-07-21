#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <unordered_map>
#include <string>
#include "PluginData.h"

#ifndef PluginManager_H
#define PluginManager_H

const char * baseModDLLName = "CubeWorldModApi.dll";

using namespace std;

class PluginManager
{
private:
	//Plugins listed by 
	unordered_map<string,PluginData> pluginList;
public:
    //Load all plugins from a specified directory
	PluginManager::PluginManager(string pluginDirectory)	{
		//For Each Metadata file in plugins dir create a plugin object
		//and add it to the hashmap
	}

	void changePluginActivation(string pluginName, bool activation)	{
		pluginList[pluginName].setActivated(activation);
	}

	void execute(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	{
		modifyResources();
		//Start cube.exe
		STARTUPINFO startupInfo;
		memset(&startupInfo, 0, sizeof(STARTUPINFO));
		startupInfo.cb = sizeof(startupInfo);
		PROCESS_INFORMATION processInfo;

		if(CreateProcess(TEXT("Cube.exe"), NULL, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &startupInfo, &processInfo))	{
			//Inject and run stuff
			executeRemoteFunction("kernel32.dll","LoadLibraryA", (void *) baseModDLLName,processInfo);
			vector<string> pluginDllList;
			//get list of plugin dlls in pluginDllList
			executeRemoteFunction(baseModDLLName, "Initialize", (void *) pluginDllList.data(), processInfo);
			
			ResumeThread(processInfo.hThread);
			CloseHandle(processInfo.hProcess);
			WaitForSingleObject(processInfo.hThread, INFINITE);
		}
		else
		{
			//log debug
			//exit
		}
	}

	void modifyResources()	{
	}

	void executeRemoteFunction(LPCSTR dllName, LPCSTR functionName, void * parameter, PROCESS_INFORMATION processInfo)	{

			LPVOID functionHandle = (LPVOID) GetProcAddress(GetModuleHandle(TEXT(dllName)), functionName);
			LPVOID remoteMem = (LPVOID) VirtualAllocEx(processInfo.hProcess, NULL, strlen(baseModDLLName) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			WriteProcessMemory(processInfo.hProcess, remoteMem, baseModDLLName, strlen(baseModDLLName) + 1, NULL);

			HANDLE thread = CreateRemoteThread(processInfo.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE) functionHandle, remoteMem, CREATE_SUSPENDED, NULL);
			if (thread == NULL)	{
				//Log debug
				//exit
			}
			ResumeThread(thread);
			CloseHandle(thread);
	}
};

#endif