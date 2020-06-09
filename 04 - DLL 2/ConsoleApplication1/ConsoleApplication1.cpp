// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <windows.h>
//#include "MyDllLab.h"
#include <iostream>

typedef int(__stdcall *f_funci)();

typedef int(__cdecl *f_sum)(int a, int b);
typedef int(__cdecl *f_mul)(int a, int b);
typedef int(__cdecl *f_div)(int a, int b);


int main()
{
	///подключ dll
	HINSTANCE hProcID = LoadLibrary(TEXT("D:\\3\\OSiSP\\MyDLLMFC\\Debug\\MyDLLMFC.dll"));

#pragma region

	if (!hProcID) {
		std::cout << "could not load the dynamic library\n" << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Dll found!!!!" << std::endl;

	/// в dll получ ссылку на ф-ю
	f_funci funci = (f_funci)GetProcAddress(hProcID, "SendMessageNumber");

	if (!funci) {
		std::cout << "could not locate the function\n" << GetLastError() << std::endl;
		FreeLibrary(hProcID);
		return EXIT_FAILURE;
	}

	int x = (funci)();
	std::cout << "SendMessage returned " << x << "\n\n";

#pragma endregion


	f_sum sum = (f_sum)GetProcAddress(hProcID, "Sum");
	f_mul mul = (f_mul)GetProcAddress(hProcID, "Mul");
	f_div div = (f_div)GetProcAddress(hProcID, "Div");



	int a, b;
	std::cout << "Enter 2 numbers: \n";
	std::cin >> a >> b;

	int summ = (sum)(a, b);
	int mull = (mul)(a, b);
	int divv = (div)(a, b);

	printf("%d + %d = %d \n", a, b, summ);
	printf("%d * %d = %d \n", a, b, mull);
	printf("%d / %d = %d \n", a, b, divv);


	FreeLibrary(hProcID);
	system("pause");
	return EXIT_SUCCESS;

}



