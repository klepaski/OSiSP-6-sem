// MyDLLMFC.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "stdafx.h"
#include "MyDLLMFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


__declspec(dllexport) int SquareInt(int param);
__declspec(dllexport) int SendMessage();

__declspec(dllexport) int Sum(int a, int b);
__declspec(dllexport) int Mul(int a, int b);
__declspec(dllexport) int Div(int a, int b);

int SquareInt(int param)
{
	return param * param;
}

int SendMessageNumber()
{
	return 100;
}

int Sum(int a, int b)
{
	return a + b;
}

int Mul(int a, int b)
{
	return a * b;
}

int Div(int a, int b)
{
	return a / b;
}



#pragma region

// CMyDLLMFCApp

BEGIN_MESSAGE_MAP(CMyDLLMFCApp, CWinApp)
END_MESSAGE_MAP()


// Создание CMyDLLMFCApp

CMyDLLMFCApp::CMyDLLMFCApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CMyDLLMFCApp

CMyDLLMFCApp theApp;


// Инициализация CMyDLLMFCApp

BOOL CMyDLLMFCApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

#pragma endregion
