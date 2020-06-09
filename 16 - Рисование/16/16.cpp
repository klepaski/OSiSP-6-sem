// 16.cpp : Определяет точку входа для приложения.
//1) нарисовать график синусоиды маленькими овалами
//2) нарисовать график синусоиды маленькими линиями

#include "stdafx.h"
#include "16.h"
#include <math.h>

#define MAX_LOADSTRING 100

void GamePaint(HDC hDC, HWND hWnd);
void SinPaint(HDC hDC, HWND hWnd);

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY16, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY16));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY16));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY16);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;							//!!!!!!!!!!!!!!!!!!!!
	PAINTSTRUCT ps;
	HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:									//!!!!!!!!!!!!!!!!
        {
			hdc = BeginPaint(hWnd, &ps);	///активация контекста графики
			//GamePaint(hdc, hWnd);
			SinPaint(hdc, hWnd);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void GamePaint(HDC hDC, HWND hWnd)					//Простейшее рисование
{
	TextOut(hDC, 10, 10, TEXT("Julia Chist"), 11);	///вывод текста
	MoveToEx(hDC, 10, 25, NULL);					///перевод курсора в новую поз
	LineTo(hDC, 100, 25);							///рисование линии (от т.курсора до указ)
	RECT rect;
	GetClientRect(hWnd, &rect);
	Rectangle(hDC, 16, 36, 72, 80);					///рисование прям-ка
	Rectangle(hDC, 34, 50, 54, 70);
	Ellipse(hDC, 40, 55, 48, 65);					///коорд прям-ка, в кот. вписан эллипс
	Ellipse(hDC, 300, 200, 580, 380);
	DrawText(hDC, TEXT("JULIA CHIST"), -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	RECT rt;														///закрашен. прям-к
	rt.left = 40; rt.top = 200; rt.right = 30; rt.bottom = 350;
	static HBRUSH brRed;
	if (!brRed) brRed = CreateSolidBrush(RGB(200, 0, 0));			///созд красную кисть
	FillRect(hDC, &rt, brRed);
}


void SinPaint(HDC hDC, HWND hWnd)
{
	int y = 0;
	double PI = 3.14;
	int X = 0, Y = 50;

	for (int i = 0; i < 500; i++)
	{
		y = (int)(sin((double)i * PI / 180) * 50);
		Ellipse(hDC, X + i, Y - y, X + i + 35, Y - y + 35);
	}

	X = 0;
	Y = 150;

	for (int i = 0; i < 1000; i+=60)
	{
		y = (int)(sin((double)i * PI / 180) * 50);
		LineTo(hDC, X + i, Y - y);
	}
}





INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
