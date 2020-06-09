// 17_5zad.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Написать программу, которая  определяет, что в выражении все скобки спарены. 
Например, (a+b)*(c-d).  Ответ YES. Но для выражения (a-(c+)   ответ NO.
*/

#include "pch.h"
#include <iostream>
#include <stack>
#include <string>

using namespace std;
bool is_correct(const string&);

int main()
{
	setlocale(0, "");
	while (true)
	{
		cout << "\nВведите выражение: ";
		string str;
		cin >> str;

		cout << (is_correct(str) ? "Скобки расставлены верно" : "Скобки расставлены неверно") << endl;
	}
}

bool is_correct(const string& str)
{
	stack< char > stack;

	for (int i = 0; i < (int)str.length(); ++i)
	{
		if (str[i] == '(')
		{
			stack.push(str[i]);
		}
		else if (str[i] == ')')
		{
			if (stack.empty() || stack.top() != '(')
			{
				return false;
			}

			stack.pop();
		}
	}
	return stack.empty();
}