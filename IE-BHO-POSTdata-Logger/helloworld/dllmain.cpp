// dllmain.cpp : DllMain ��ʵ�֡�

#include "stdafx.h"
#include "resource.h"
#include "helloworld_i.h"
#include "dllmain.h"

ChelloworldModule _AtlModule;

// DLL ��ڵ�
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)  
    {  
        DisableThreadLibraryCalls(hInstance);  
    }  
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
