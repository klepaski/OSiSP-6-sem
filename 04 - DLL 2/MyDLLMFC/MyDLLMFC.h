// MyDLLMFC.h: основной файл заголовка для библиотеки DLL MyDLLMFC
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMyDLLMFCApp
// Реализацию этого класса см. в файле MyDLLMFC.cpp
//

class CMyDLLMFCApp : public CWinApp
{
public:
	CMyDLLMFCApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
