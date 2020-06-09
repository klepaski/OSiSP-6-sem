// OS_Lab_9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
	порт заверш - сист.очередь, в кот. 1 процесс посылает пакеты, 2 - считывает
	он связ. с файлом

	записал -> в порт пакет с числом запис.байтов
	поток считывает этот пакет, выдает сообщ и заверш работу
*/

#include "pch.h"
#include <windows.h> 
#include <iostream> 
using namespace std;


HANDLE hFile;
OVERLAPPED ovl;

HANDLE hCompletionPort;		/// порт завершения


DWORD WINAPI thread(LPVOID)
{
	int i = 0;				/// кол-во полученных пакетов 
	DWORD dwNumberOfBytes;	/// кол-во переданных байтов 
	ULONG ulCompletionKey;	/// ключ файла 
	LPOVERLAPPED lpOverlapped; /// ук на структ типа OVERLAPPED 
	cout << "The thread is started." << endl;

	// подключаем поток к порту 

	while (GetQueuedCompletionStatus(
		hCompletionPort,	/// дескриптор порта завершения 
		&dwNumberOfBytes,	/// кол-во переданных байтов 
		&ulCompletionKey,	/// ключ файла 
		&lpOverlapped,		/// ук на структ типа OVERLAPPED 
		INFINITE))			/// бесконечное ожидание 
	{
		if (ulCompletionKey == 0)	//провер пакет на завершение вывода
		{
			cout << endl << "The thread is finished." << endl;
			break;
		}
		else
			cout << "\tPacket: " << ++i
			<< "\n Number of bytes: " << dwNumberOfBytes << "\nCompletion key: " << ulCompletionKey << endl;

	}
	return 0;
}


DWORD WINAPI thread2(LPVOID)
{
	DWORD dwBytesWrite;
	DWORD dwRet;
	char a[250] = "hello ";
	if (!WriteFile(
		hFile,		/// дескриптор файла 
		&a,			/// адрес буфера, откуда идет запись 
		sizeof(a),	/// кол-во записываемых байтов 
		&dwBytesWrite, /// кол-во записанных байтов 
		&ovl		/// запись асинхронная 
	))
	{
		dwRet = GetLastError();
		if (dwRet == ERROR_IO_PENDING)
			cout << "Write file pending." << endl;
		else
		{
			cout << "Write file failed." << endl
				<< "The last error code: " << dwRet << endl;
			return 0;
		}
	}
	WaitForSingleObject(hFile, INFINITE);
	return 0;
}


DWORD WINAPI thread3(LPVOID)
{
	char Buffer[250] = "";
	DWORD dwNumberOfBytes;
	ReadFile(hFile, Buffer, sizeof(Buffer), &dwNumberOfBytes, &ovl);
	std::wcout << "Read: " << Buffer << '\n';
	return 0;
}


int main()
{
	ULONG ulKey;
	HANDLE hThread;
	HANDLE hThread2;
	HANDLE hThread3;
	DWORD dwThreadID; /// массив для идентификаторов потоков 

	// инициализируем структуру OVERLAPPED 
	ovl.Offset = 0;		/// младшая часть смещения
	ovl.OffsetHigh = 0; /// старшая часть смещения
	ovl.hEvent = 0;		/// события нет 

	// запрашиваем ключ файла 
	cout << "Input a number for file key (not zero)";
	cin >> ulKey;

	if (ulKey == 0)
	{
		cout << "The file key can't be equal to zero."
			<< "Press any key to exit." << endl;
		return 0;
	}

	// создаем файл для записи данных 
	hFile = CreateFile(
		TEXT("D:/my.txt"),
		GENERIC_ALL,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_FLAG_OVERLAPPED,	/// асинхронный доступ к файлу 
		NULL					/// шаблона нет 
	);

	// проверяем на успешное создание 
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish." << endl;
		return 0;
	}
	Sleep(100);

	// создаем порт завершения и подключаем к нему файл 
	hCompletionPort = CreateIoCompletionPort(
		hFile,	/// дескриптор файла 
		NULL,	/// новый порт 
		ulKey,	/// ключа файла 
		0		/// один поток 
	);

	// проверяем на успешное создание 
	if (hCompletionPort == NULL)
	{
		cerr << "Create completion port failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish." << endl;
		
		return 0;
	}
	// запускаем поток 
	hThread = CreateThread(NULL, 0, thread, NULL, 0,  &dwThreadID);
	hThread2 = CreateThread(NULL, 0, thread2, NULL, 0, &dwThreadID);
	Sleep(100);
	hThread3 = CreateThread(NULL, 0, thread3, NULL, 0, &dwThreadID);

	// пишем данные в файл 

	// посылаем пакет с командой на завершение потока 
	PostQueuedCompletionStatus(
		hCompletionPort,	/// дескриптор потока 
		0,					/// нет передачи 
		0,					/// ключ завершения 
		NULL);				/// нет структуры типа OVERLAPPED 
	

	WaitForSingleObject(hThread, INFINITE);	// ждем завершения потока 
	
	// закрываем дескрипторы 
	CloseHandle(hFile);
	CloseHandle(hCompletionPort);
	CloseHandle(hThread);
	CloseHandle(hThread2);
	CloseHandle(hThread3);

	system("pause");
	return 0;
}


