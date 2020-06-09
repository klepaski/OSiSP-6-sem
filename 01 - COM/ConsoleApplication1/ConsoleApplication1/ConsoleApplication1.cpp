// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <objbase.h>
#include "..\ConsoleApplication2\int.h"
using namespace std;

// GUID (присв спец. утилитой, здесь не интересен)
static const IID IID_IX = { 0x32bb8320, 0xb41b, 0x11cf, {0xa6, 0xbb,0x0,0x80,0xc7,0xb2,0xd6,0x82} };
static const IID IID_IY = { 0x32bb8321, 0xb41b, 0x11cf, {0xa6, 0xbb,0x0,0x80,0xc7,0xb2,0xd6,0x82} };


// Компонент (реализ инт COM)
class CA : public IX, public IY	
{
	virtual HRESULT __stdcall QueryInterface(const IID&  iid, void** ppv);	//методы инт IUnknown:
	virtual ULONG __stdcall AddRef() { return 0; }
	virtual ULONG __stdcall Release() { return 0; }

	virtual void __stdcall Fx() { cout << "Hi, from FX\n"; };
	virtual void __stdcall Fx1(int i) { cout << i * i  << "\n"; };
	virtual void __stdcall Fy() { cout << "Hi, from FY\n"; };
};




HRESULT __stdcall CA::QueryInterface(const IID& iid, void ** ppv)//возвр ук-ль на инт -> м. исп методы (Fy,Fx) (GUID, ук-ль на объ инт)
{
	if (iid == IID_IX)
	{
		cout << "return a pointer to IX\n";
		*ppv = static_cast<IX*>(this);
	}
	else if (iid == IID_IY)
	{
		cout << "return a pointer to IY\n";
		*ppv = static_cast<IY*>(this);
	}
	else
	{
		cout << "Interface not supported\n";
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}


IUnknown* CreateInstance()
{
	IUnknown* pI = static_cast<IY*> (new CA);
	pI->AddRef();
	return pI;
}



//Клиент
int main()
{
	HRESULT hr,hh;
	cout << "Get a pointer to Iunknown\n";
	IUnknown* pIUnknown = CreateInstance();

	cout << "Get a pointer to IX\n";
	IX* pIX = NULL;
	IY* pIY = NULL;
	hr = pIUnknown->QueryInterface(IID_IX, (void**)&pIX);
	hh = pIUnknown->QueryInterface(IID_IY, (void**)&pIY);

	if (SUCCEEDED(hr))
	{
		cout << "IX gotcha successfully!\n";
		pIX->Fx();
		int num; cout << "Enter number: "; cin >> num;;
		pIX->Fx1(num);
	}

	if (SUCCEEDED(hh))
	{
		cout << "IY gotcha successfully!\n";
		pIY->Fy();
	}

	system("pause");
	return 0;
}

