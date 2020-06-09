//����������� ��������� ����������� �� ������, �� �� ���������� ������������� �� �������������� �����, 
//���� ����������� �� ����� �� ����� ��������� � ��������� ��������


// + 2 ����� ���������: ���� ���� ���-��� ++10, ++100
// + 2 ������: �. ������ ����� ���������
// + 2 ����� ���������: ����� ������ � ����� + ������ (���� ����)

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

HANDLE hThread1;
DWORD IDThread1;
HANDLE hThread2;
DWORD IDThread2;
HANDLE hThread3;
DWORD IDThread3;
DWORD dwRet;
CRITICAL_SECTION cs;



void CALLBACK a_proc10(DWORD p)
{
	DWORD *ptr = (DWORD*)p;
	///std::cout << "The async proc10 is called!" << std::endl;
	*ptr += 10;
	cout << "The async proc10 returned!!\n";
}



void CALLBACK a_proc100(DWORD p)
{
	DWORD *ptr = (DWORD*)p;
	///std::cout << "The async proc100 is called!" << std::endl;
	*ptr += 100;
	cout << "The async proc100 returned!!\n";
}




void CALLBACK a_writeFile(DWORD p)
{
	string buf;
	cout << "The async proc writeFile is called!\n"
		 << "Enter your string: ";

	EnterCriticalSection(&cs);
	getline(cin, buf);
	std::ofstream out;       // ����� ��� ������
	out.open("D:\\8os.txt"); // �������� ���� ��� ������

	if (out.is_open()) out << buf;

	LeaveCriticalSection(&cs);
	cout << "The async proc writeFile ended!!\n";
}




void CALLBACK a_readFile(DWORD p)
{
	cout << "\n\nThe async proc readFile is called!\n";
	std::string line;

	EnterCriticalSection(&cs);
	std::ifstream in("D:\\8os.txt"); // �������� ���� ��� ������

	if (in.is_open())
		while (getline(in, line)) cout << line << "\n";

	in.close();     // ��������� ����
	LeaveCriticalSection(&cs);
	cout << "The async proc readFile ended!!\n";
}



//Now thread is defined

DWORD WINAPI add1(LPVOID ptr)
{
	DWORD* zz = (DWORD*)ptr;
	cout << "Thread says: initial count is " << *zz << "\n";
	SleepEx(INFINITE, TRUE);
	cout << "Thread says: Final count from async proc is " << *zz << "\n\n\n";
	getchar();
	return 0;
}

DWORD WINAPI add2(LPVOID ptr)
{
	DWORD* zz = (DWORD*)ptr;
	cout << "Thread says: initial count is " << *zz << std::endl;
	SleepEx(INFINITE, TRUE);
	cout << "Thread says: Final count from async proc is " << *zz << "\n\n\n";
	getchar();
	return 0;
}

DWORD WINAPI file(LPVOID ptr)
{
	cout << "Thread file says: START \n";
	SleepEx(INFINITE, TRUE);
	cout << "Thread file says: END! \n\n\n";
	getchar();
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD count = 10;

	InitializeCriticalSection(&cs);

	hThread1 = CreateThread(NULL, 0, add1, &count, 0, &IDThread1);	///������ �����
	Sleep(100);	///�������� ������� ������ ����� (���� �������� �����������)
	
	dwRet = QueueUserAPC(a_proc10, hThread1, (DWORD)&count);	///���.���� ����� ����� ��������� � ���� ������ � ��� �� �-�
	hThread2 = CreateThread(NULL, 0, add2, &count, 0, &IDThread2);
	Sleep(100);
	
	dwRet = QueueUserAPC(a_proc100, hThread2, (DWORD)&count);
	hThread3 = CreateThread(NULL, 0, file, NULL, 0, &IDThread3);
	Sleep(100);
	
	dwRet = QueueUserAPC(a_writeFile, hThread3, NULL);
	dwRet = QueueUserAPC(a_readFile, hThread3,NULL);
	
	WaitForSingleObject(hThread1, INFINITE);///���.������� �������� � ���� ������ ������
	CloseHandle(hThread1);
	
	WaitForSingleObject(hThread2, INFINITE);
	CloseHandle(hThread2);
	
	WaitForSingleObject(hThread3, INFINITE);
	CloseHandle(hThread3);

	getchar();
	return 0;
}
