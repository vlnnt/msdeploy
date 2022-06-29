/*****************************************************************************\
*                                                                             *
* Title: Main.cc                                                              *
*                                                                             *
* Description: Main file, with client implementation.                         *
*                                                                             *
* Author: vlnnt								      *
*                                                                             *
* IDE: Visual Studio 2019                                                     *
*                                                                             *
\*****************************************************************************/

#include "Injection.h"

int main() {

	setlocale(LC_ALL, "RU");

	Injection injectionInstance;
	string DLLPath{};
	int PID{};

	injectionInstance.GetProcList();
	injectionInstance.Client(DLLPath, PID);
	injectionInstance.DLLInject(DLLPath, PID);

	return 0;
}