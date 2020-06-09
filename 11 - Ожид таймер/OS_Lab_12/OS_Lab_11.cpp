// ож. таймер - сраб в опр момент в буд (абс выраж или смещ в мин/сек)
// созд ож.таймер + запуск поток + таймер сраб и поток что-то сделает

#include "pch.h"
#include <windows.h> 
#include <iostream> 
using namespace std;
#define _SECOND 10000000 /// одна секунда для ожид таймера 
HANDLE hTimer;			 /// ожид таймер 

DWORD WINAPI thread(LPVOID)
{
	WaitForSingleObject(hTimer, INFINITE); ///ждем сигнал от ожид.тайм
	cout<<"\nThe timer is signaled." << endl; ///вывод сообщ
	return 0;
}

int main()
{
	cout << "start" << endl;
	HANDLE hThread;
	DWORD IDThread;
	_int64 qwTimeInterval; /// t задержки для таймера 

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);	///созд ожид тайм
	if (hTimer == NULL)
		return GetLastError();

	qwTimeInterval = -3 * _SECOND;	///t задержки таймера 3 сек
	
	if (!SetWaitableTimer(				///иниц таймер
		hTimer,							/// дескриптор таймера 
		(LARGE_INTEGER*)&qwTimeInterval, /// временной интервал 
		0,		/// непериодический таймер 
		NULL,	/// процедуры завершения нет 
		NULL,	/// параметров к этой процедуре нет 
		FALSE	/// режим сбережения энергии не устанавливать 
	))
	{
		cout << "Set waitable timer failed." << endl
		<< "The last error code: " << GetLastError() << endl;
		return 0;
	}

	hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);	///запуск поток
	if (hThread == NULL)
		return GetLastError();
	WaitForSingleObject(hThread, INFINITE);	///ждем пока поток закончит работу
	CloseHandle(hThread);					///закр дескрипторы
	CloseHandle(hTimer);
	system("pause");
	return 0;
}