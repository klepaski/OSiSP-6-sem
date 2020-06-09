// ож. таймер - сраб в опр момент в буд (абс выраж или смещ в мин/сек)
// созд ож.таймер + запуск поток + таймер сраб и поток что-то сделает

// осн. процесс создает 2 потока и таймер
// первый поток пишет в текст файл и завершается
// когда таймер сраб, второй поток счит содержимое текст файла и выводит на консоль

#include "pch.h"
#include <iostream>
#include <windows.h> 

using namespace std;
#define _SECOND 10000000 /// одна секунда для ожидающего таймера 
HANDLE hTimer;			 /// ожидающий таймер 

DWORD WINAPI thread1(LPVOID)
{
	TCHAR Buffer[256] = TEXT("Hello from 5 group");
	HANDLE hOut;
	DWORD dwNumberOfBytes;
	FILE* fp;
	TCHAR stdPath[30] = TEXT("D:\\Lab11.txt");
	hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOut == INVALID_HANDLE_VALUE) {
		printf("ERROR %x \n", GetLastError());
		getchar();

		return 2;
	}

	else
	{
		WriteFile(hOut, Buffer, 256, &dwNumberOfBytes, NULL);
		printf("__File WRITE:");
		getchar();
		CloseHandle(hOut);
	}
	return 0;
}

DWORD WINAPI thread2(LPVOID)
{
	cout << endl << "Wait Timer" << endl;
	WaitForSingleObject(hTimer, INFINITE); /// ждем сигнал от ожид таймера
	TCHAR Buffer[256];	///выводим сообщ
	HANDLE hIn;
	DWORD dwNumberOfBytes;
	FILE* fp;
	TCHAR stdPath[30] = TEXT("D:\\Lab11.txt");
	hIn = CreateFile(stdPath, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hIn == INVALID_HANDLE_VALUE) {
		printf("ERROR %x \n", GetLastError());
		getchar();
		return 2;
	}
	else
	{
		printf("__File READ:");
		ReadFile(hIn, Buffer, 256, &dwNumberOfBytes, NULL);
		wprintf(Buffer);
		getchar();
		CloseHandle(hIn);
	}
	return 0;
}

int main()
{
	cout << "start" << endl;
	HANDLE hThread1;
	HANDLE hThread2;
	DWORD IDThread1;
	DWORD IDThread2;

	_int64 qwTimeInterval; /// время задержки для таймера 

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);	///созд ожид таймер
	if (hTimer == NULL)
		return GetLastError();
	qwTimeInterval = -10 * _SECOND;	///t задержки таймера 10 сек
	if (!SetWaitableTimer(		///иниц таймер
		hTimer,					/// дескриптор таймера 
		(LARGE_INTEGER*)&qwTimeInterval, /// временной интервал 
		0, /// непериодический таймер 
		NULL, /// процедуры завершения нет 
		NULL, /// параметров к этой процедуре нет 
		FALSE /// режим сбережения энергии не устанавливать 
	))
	{
		cout << "Set waitable timer failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		return 0;
	}
	hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, &IDThread1);	///запуск поток
	hThread2 = CreateThread(NULL, 0, thread2, NULL, 0, &IDThread2);
	if (hThread1 == NULL)
		return GetLastError();
	if (hThread2 == NULL)
		return GetLastError();
	WaitForSingleObject(hThread1, INFINITE);	///ждем пока поток закончит работу
	WaitForSingleObject(hThread2, INFINITE);
	CloseHandle(hThread1);	///закр дескрипторы
	CloseHandle(hThread2);
	CloseHandle(hTimer);
	system("pause");
	return 0;
}

