/*****************************************************************************\
*                                                                             *
* Title: Injection.cc                                                         *
*                                                                             *
* Description: Implementation of functions of the class "Injection".          *
*                                                                             *
* Author: vlnnt						                      *
*                                                                             *
* IDE: Visual Studio 2019                                                     *
*                                                                             *
\*****************************************************************************/

#include "Injection.h"

Injection::Injection() : _hProcessSnapshot{}, _pe32{}, _hRemoteThread{}, _handleProcess{}, _allocString{} {}

void __stdcall Injection::GetProcList() {
	
	try {

		_hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		_pe32.dwSize = sizeof(PROCESSENTRY32);

		cout << "=================================== LIST =========================================\n";
		while (Process32Next(_hProcessSnapshot, &_pe32)) {
			cout << '\n' << "----Parent Process ID: " << '[' << _pe32.th32ParentProcessID << ']' << '\n';
			cout << "\t |\n";
			cout << "\t |____";
			cout << "Child Process ID: " << '[' << _pe32.th32ProcessID << ']';
			_tprintf(TEXT("\t\tProcess Name: %s"), _pe32.szExeFile);
			cout << '\n';
		}
		cout << "\n=================================== LIST =========================================\n";
	}

	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
}

void __stdcall Injection::DLLInject(string DLLPath, int PID) {

	try {

		_handleProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		LPVOID LoadLibraryExW = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");

		_allocString = (LPVOID)VirtualAllocEx(_handleProcess, NULL, strlen(DLLPath.c_str()) + 1, MEM_COMMIT, PAGE_READWRITE);
		WriteProcessMemory(_handleProcess, _allocString, (LPVOID)DLLPath.c_str(), strlen(DLLPath.c_str()) + 1, NULL);

		_hRemoteThread = CreateRemoteThread(_handleProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryEx, _allocString, NULL, NULL);
		WaitForSingleObject(_hRemoteThread, INFINITE);
	}

	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
}

void Injection::Client(string DLLPath, int PID) {

	cout << "\nEnter DLL Location: ";
	cin >> DLLPath;
	cout << "Enter Child Process ID for inject: ";
	cin >> PID;
}

Injection::~Injection() {
	CloseHandle(_hProcessSnapshot);
	VirtualFreeEx(_handleProcess, _allocString, 0, MEM_RELEASE);
	CloseHandle(_hRemoteThread);
	CloseHandle(_handleProcess);
}