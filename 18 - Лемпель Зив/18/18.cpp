// OSLab_19.cpp: определяет точку входа для консольного приложения.
//

#include "pch.h"
#include <string>
#include <iostream>
#include <list>
using namespace std;

string ConvertToBin(int a)
{
	int  b;
	string str = "";
	b = a;
	while (b > 0)
	{
		a = b;
		if (a % 2 == 0) str += '0';
		else str += '1';
		b = a / 2;
	}
	if (str.length() != 4) str += string(4 - str.length(), '0');
	reverse(str.begin(), str.end());
	return str;
}

int main()
{
	while (true) {
		int i = 0;
		int size = 1;
		string ss = "";					//juliachistyakova
		string buffer;
		list<string> current, next, result;
		typedef list<string>::iterator Iterator;
		
		cout << "Enter text: ";
		cin >> ss;
		cout << "\n";

		string temp = ss;

		while (ss.length() != 0)
		{
			buffer += ss[i];												///j...
			Iterator iter = find(current.begin(), current.end(), buffer);

			if (iter != current.end()) i++;		///уже есть
			else
			{
				if (i + 1 <= ss.length())		///не последняя
				{
					current.insert(current.end(), buffer);
					next.insert(next.end(), string(1, ss[i + 1]));
					result.insert(result.end(), ConvertToBin(size++));
				}
				ss = ss.erase(0, i + 1);
				buffer = "";
				i = 0;
			}
		}

		for (Iterator i_cur = current.begin(), i_next = next.begin(), i_res = result.begin(); i_cur != current.end(); ++i_cur, ++i_next, ++i_res)
		{
			cout << *i_cur << "\t|" << *i_next << "\t|" << *i_res << "\n";
		}

		string resultStr = "";
		while (temp.length() != 0)
		{
			ss += temp[i];

			if (find(current.begin(), current.end(), ss) != current.end())	i++;
			else
			{
				i--;
				ss.erase(ss.end() - 1, ss.end());
				for (Iterator iter2 = current.begin(), iter3 = result.begin(); iter2 != current.end(); ++iter2, ++iter3)
				{
					if (*iter2 == ss)
					{
						resultStr += *iter3 + " ";
						ss = "";
						temp.erase(0, i + 1);
						i = 0;
						break;
					}
				}
			}
		}
		cout << "encoded\n" << resultStr << "\n";
		buffer = "";
		i = 0;
		temp = "";

		while (resultStr.length() != 0)
		{
			if (resultStr[i] != ' ')	buffer += resultStr[i++];
			else
			{
				resultStr.erase(0, i + 1);

				for (Iterator iter2 = current.begin(), iter3 = result.begin(); iter2 != current.end(); ++iter2, ++iter3)
				{
					if (*iter3 == buffer)
					{
						temp += *iter2;
						buffer = "";
						i = 0;
						break;
					}
				}
			}
		}
		cout << "\n" << temp << "\n\n";
	}
	system("pause");
}

