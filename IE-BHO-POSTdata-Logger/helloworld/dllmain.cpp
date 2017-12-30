// dllmain.cpp : DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "helloworld_i.h"
#include "dllmain.h"

ChelloworldModule _AtlModule;

// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)  
    {  
        DisableThreadLibraryCalls(hInstance);  
    }  
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
