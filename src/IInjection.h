/*****************************************************************************\
*                                                                             *
* Title: IInjection.h                                                         *
*                                                                             *
* Description: Interface of basic functions for manipulating processes.       *
*                                                                             *
* Author: vlnnt						                      *
*                                                                             *
* IDE: Visual Studio 2019                                                     *
*                                                                             *
\*****************************************************************************/

#pragma once
#ifndef I_INJECTION_H
#define I_INJECTION_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>

using namespace std;

class IInjection {
public:
	virtual void __stdcall GetProcList() = 0;
	virtual void __stdcall DLLInject(string DLLPath, int PID) = 0;
};

#endif // !I_INJECTION_H