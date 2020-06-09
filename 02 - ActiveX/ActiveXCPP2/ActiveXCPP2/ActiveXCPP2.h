#pragma once

// ActiveXCPP2.h: основной файл заголовка для ActiveXCPP2.DLL

#if !defined( __AFXCTL_H__ )
#error "включить afxctl.h до включения этого файла"
#endif

#include "resource.h"       // основные символы


// CActiveXCPP2App: реализацию см. в файле ActiveXCPP2.cpp.

class CActiveXCPP2App : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

