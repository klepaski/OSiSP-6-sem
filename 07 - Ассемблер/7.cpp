// 7asm.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
1. Реализовать код на ассемблере для нахождения наибольшего общего делителя двух целых коротких положительных чисел. Алгоритм Евклида состоит в следующем.
		1.	Ввести А и В.
		2.	Если А=В, то конец. Вывести А.
		3.	Если А> В , то принять А=А-В. Переход на шаг 1.
		4.	Если В> А , то принять В=В-А. Переход на шаг 1
2. Реализовать код на языке Ассемблера для отыскания наибольшего общего делителя трех коротких положительных чисел.
3. Проверить, стоит ли в третьем разряде справа двоичного числа 1 или 0.
4. Скопировать на базе приведенного примера одну строку в другую с заменой последней буквы первой строки на символ $.
5. Посчитать на сопроцессоре формулу:
	 Если a>b, то вернуть a^2 иначе вернуть b^2.

*/

#include "pch.h"
#include <iostream>

void out()
{
	std::cout << "don't have 1" << std::endl;
}
void out2()
{
	std::cout << "have 1" << std::endl;
}
void fmore()
{
	std::cout << "'a>b' \na*a:" << std::endl;
}
void fless()
{
	std::cout << "'a<b' \nb*b:" << std::endl;
}
void feql()
{
	std::cout << "'a=b' \nb*b:" << std::endl;
}
void sum(int a, int b)
{
	printf("%d\n", a + b);
}

int  main()
{
	setlocale(LC_CTYPE, "");
	short a, b, x;
	std::cout << "1. Введите 2 числа: " << std::endl;						// НОД 2 ЧИСЕЛ ПО АЛГ ЕВКЛИДА
	std::cin >> a;
	std::cin >> b;

	_asm
	{
		mov ax, a
		mov bx, b
		start : cmp ax, bx
				je end_start
				jg c1
				jl c2
		c1 :
			sub ax, bx
			jmp start
		c2 :
			sub bx, ax
			jmp start
		end_start :
			mov x, ax
	}
	std::cout << "NOD(" << a << "," << b << ") " << x << std::endl << std::endl;

	short c, d, e, y;
	std::cout << "2. Введите 3 числа: " << std::endl;					//НОД 3 ЧИСЕЛ
	std::cin >> c;
	std::cin >> d;
	std::cin >> e;

	_asm
	{
		mov ax, c
		mov bx, d
		start2 :
		cmp ax, bx
			je end_start2
			jg c3
			jl c4
			c3 :
		sub ax, bx
			jmp start2
			c4 :
		sub bx, ax
			jmp start2
			end_start2 :
		mov y, ax
			mov ax, y
			mov bx, e
			start3 : cmp ax, bx
			je end_start3
			jg c5
			jl c6
			c5 :
		sub ax, bx
			jmp start3
			c6 :
		sub bx, ax
			jmp start3
			end_start3 :
		mov y, ax
	}

	std::cout << "NOD(" << c << "," << d << "," << e << ") " << y << std::endl << std::endl;


	std::cout << "3. Введите число: " << std::endl;						// СТОИТ ЛИ В 3 РАЗРЯДЕ СПРАВА 1 ИЛИ 0?
	short el = 0;
	std::cin >> el;
	_asm
	{
		mov cx, 0
		mov ax, el
		mov bx, 128
		Mystart: cmp cx, 5
				 je lop1
				 jl lop2
				 jg end_Mystart
		lop1 :
			and ax, bx
			cmp ax, 0
			je lop3
			jg lop4
			jl lop4
		lop3 :
			call out			;не один
			jmp end_Mystart
		lop4 :
			call out2			;один
			jmp end_Mystart
		lop2 :
			shr bx, 1			;лог. сдвиг вправо
			inc cx
			jmp Mystart
		end_Mystart :
	}

	char* q = new char[6]{ 'h','e','l','l','o' };								// СКОПИРОВАТЬ СТРОКУ В ДРУГУЮ С ЗАМЕНОЙ ПОСЛ. СИМВОЛА НА $
	std::cout << std::endl << "4. Исходная строка: " << q << std::endl;
	char* p;
	_asm
	{
		mov eax, dword ptr[q]
		mov dword ptr[p], eax
		mov eax, 1
		shl eax, 2
		mov ecx, dword ptr[p]
		mov byte ptr[ecx + eax], '$'
	}
	std::cout << "\tСтрока с заменой последнего символа:" << p << std::endl;

	float aa, bb;
	std::cout << "\n5. Введите числа a, b" << std::endl;					// ЕСЛИ A>B ВЕРНУТЬ А^2, ИНАЧЕ B^2
	std::cin >> aa;
	std::cin >> bb;
	_asm
	{
		FINIT			; иниц.сопроц
		FLD aa			; загрузка в ST(0) операнда с именем аа
		FLD bb
		FUCOMI st, st(1)
		ja c11
		jb c22
		je c33
		c22 :
		call fmore
			FSTP bb		; запись рез-та в пер-ную памяти
			FMUL aa		; умножение
			loop END
			c11 :
		call fless
			FMUL bb
			loop END
			c33 :
		call feql
			FMUL bb
			loop END
			END :
		FST aa
	}
	std::cout << aa << std::endl;
	getchar();
	system("pause");
	return 0;
}