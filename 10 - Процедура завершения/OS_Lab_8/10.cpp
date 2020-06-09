///Процедура  завершения асинхронных операций с файлами запускается в следующем случае :
///-над файлом выполняется асинхронная операция ввода - вывода;
///-когда асинхронная операция ввода - вывода будет завершена, запускается указанная процедура завершения.


//1.	Доб в процедуру завершения вывод времени завершения операции записи в файл
//2.	Созд 2 процедуру завершения, запустите ее после завершения второй операции записи в тот же файл (она после первой)



#include "pch.h"
#include <windows.h> 
#include <iostream> 
#include <string>
#include <stdio.h>
#include <time.h>

// процедура завершения ввода-вывода 
using namespace std;

const string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%X", &tstruct);
	return buf;
}

VOID CALLBACK Proc2(
	DWORD dwErrorCode,					/// код возврата 
	DWORD dwNumberOfBytesTransferred,	/// кол-во переданных байтов 
	LPOVERLAPPED lpOverlapped			/// асинх передача данных 
)
{
	cout << endl << endl << "<< --- Is async proc 2" << endl;
	cout << currentDateTime() << " Процедура завершена с параметрами: " << endl
		<< "Код ошибки: " << dwErrorCode << endl
		<< "\tЧисло  записанных байтов: " << dwNumberOfBytesTransferred <<
		endl
		<< "\tOffsets: " << (*lpOverlapped).OffsetHigh << ' '
		<< (*lpOverlapped).Offset << endl;
}

VOID CALLBACK completion_routine(
	DWORD dwErrorCode,					/// код возврата 
	DWORD dwNumberOfBytesTransferred,	/// кол-во переданных байтов 
	LPOVERLAPPED lpOverlapped			/// асинх передача данных 
)
{
	cout << endl << endl << "<< --- Is async proc 1" << endl;
	cout << currentDateTime() <<" Процедура завершена с параметрами: " << endl
		<< "Код ошибки: " << dwErrorCode << endl
		<< "\tЧисло  записанных байтов: " << dwNumberOfBytesTransferred <<
		endl
		<< "\tOffsets: " <<(*lpOverlapped).OffsetHigh << ' '
		<<(*lpOverlapped).Offset << endl;
}



int main()
{
	setlocale(LC_ALL, "Rus");
	VOID (__stdcall *funEnd)(DWORD,DWORD, LPOVERLAPPED) = &completion_routine;
	HANDLE hFile;		/// дескриптор файла 
	OVERLAPPED ovl;		/// структ упр-я асинх доступом к файлу 

	// инициализируем структуру OVERLAPPED 
	ovl.Offset = 0;		/// младшая часть смещения равна 0 
	ovl.OffsetHigh = 0; /// старшая часть смещения равна 0 

	// создаем или открываем файл для записи данных 
	hFile = CreateFile(L"D:\\8os.txt",	/// имя файла 
		GENERIC_WRITE,					/// запись в файл 
		FILE_SHARE_WRITE,				/// совместный доступ к файлу 
		NULL,							/// защиты нет 
		OPEN_ALWAYS,					/// откр или созд новый файл 
		FILE_FLAG_OVERLAPPED,			/// асинх доступ к файлу 
		NULL							/// шаблона нет 
	);

	// проверяем на успешное создание 
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Файл не создан" << endl << "Ошибка: " << GetLastError() << endl;
		cout << "Нажмите любую клавишу";
		cin.get();
		return 0;
	}

	// пишем данные в файл 
	for (int i = 0; i < 10; ++i)
	{
		if (i == 1)
		{
			funEnd = &Proc2;
		}
		else
		{
			funEnd = &completion_routine;
		}
		DWORD dwRet;
		if (!WriteFileEx(
			hFile,		/// дескриптор файла 
			&i,			/// адрес буфера, откуда идет запись 
			sizeof(i),	/// кол-во записываемых байтов 
			&ovl,		/// запись асинхронная 
			funEnd		/// процедура завершения 
		))
		{
			dwRet = GetLastError();
			if (dwRet == ERROR_IO_PENDING)
				cout << "Write file pending." << endl;
			else
			{
				cout << "Запись закончилась ошибкой" << endl
					<< "Код ошибки: " << dwRet << endl;
				return 0;
			}
		}
		// ждем, пока сработает асинх процедура 
		// завершения операции вывода 
		SleepEx(INFINITE, TRUE);		/// увеличивает смещение в файле 
		ovl.Offset += sizeof(i);
		cout << "Запись завершена" << endl;
	}
	system("pause");
	return 0;
}
