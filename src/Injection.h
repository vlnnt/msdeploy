/*****************************************************************************\
*                                                                             *
* Title: Injection.h                                                          *
*                                                                             *
* Description: Redefining interface fields "IInjection".		      *
*                                                                             *
* Author: vlnnt								      *
*                                                                             *
* IDE: Visual Studio 2019                                                     *
*                                                                             *
\*****************************************************************************/

#pragma once
#ifndef INJECTION_H
#define INJECTION_H

#include "IInjection.h"

class Injection : public IInjection {
public:
	Injection();
	~Injection();

	void __stdcall GetProcList() override;
	void __stdcall DLLInject(string DLLPath, int PID) override;

	void Client(string DLLPath, int PID);

private:
	HANDLE _hProcessSnapshot;
	PROCESSENTRY32 _pe32;
	HANDLE _hRemoteThread;
	HANDLE _handleProcess;
	LPVOID _allocString;
};

#endif // !INJECTION_H