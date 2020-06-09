// 12.cpp : Определяет точку входа для приложения.

// обработчик нажатия вирт.клавиши VK_END (end)
// по этой клавише каретка д.устан-ся прямо за последним символом набр.текста

//написать обработчик F1 для запуска внеш исполн. файла


#include "stdafx.h"
#include "12.h"

#define BUFSIZE 65535
#define SHIFTED 0x8000 
#define MAX_LOADSTRING 100

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
    LoadStringW(hInstance, IDC_MY12, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY12));

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



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY12));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY12);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
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

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//







// обработчик нажатия вирт.клавиши VK_END (end)
// по этой клавише каретка д.устан-ся прямо за последним символом набр.текста

//написать обработчик F1 для запуска внеш исполн. файла

LRESULT CALLBACK WndProc(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;                   // заголовок устройства 
	TEXTMETRIC tm;             // структура для метрики текста 
	static DWORD dwCharX;      // ширина символа
	static DWORD dwCharY;      // высота символа
	static DWORD dwClientX;    // ширина клиентской области 
	static DWORD dwClientY;    // высота клиентской области 
	static DWORD dwLineLen;    // длина линии
	static DWORD dwLines;      // количество строк в клиентской области 
	static int nCaretPosX = 0; // позиции каретки по оси Х
	static int nCaretPosY = 0; // позиция каретки по оси У
	static int nCharWidth = 0; // ширина символа
	static int cch = 0;        // число символов в буфере
	static int nCurChar = 0;   // номер текущего символа 
	static PTCHAR pchInputBuf; // входной буфер
	int i, j;                  // переменные цикла
	int cCR = 0;               // счетчик возвратов каретки 
	int nCRIndex = 0;          // номер последнего возврата 
	int nVirtKey;              // код виртуальной клавиши
	TCHAR szBuf[128];          // временный буфер 
	TCHAR ch;                  // текущий символ 
	PAINTSTRUCT ps;            // структура необходимая для рисования
	RECT rc;                   // прямоугольник для рисования текста по DrawText 
	SIZE sz;                   // метрика строки
	COLORREF crPrevText;       // предыдущий цвет символов
	COLORREF crPrevBk;         // предыдущий цвет фона

	size_t * pcch;
	HRESULT hResult;
	static int X = 0, Y = 0;

	switch (uMsg)
	{
	case WM_CREATE:
		// Получаем метрику текущего шрифта. 
		hdc = GetDC(hwndMain);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwndMain, hdc);

		// Save the average character width and height.
		dwCharX = tm.tmAveCharWidth;
		dwCharY = tm.tmHeight;

		// Allocate a buffer to store keyboard input.
		pchInputBuf = (LPTSTR)GlobalAlloc(GPTR, BUFSIZE * sizeof(TCHAR));
		return 0;

	case WM_SIZE:
		// Save the new width and height of the client area.
		dwClientX = LOWORD(lParam);
		dwClientY = HIWORD(lParam);

		dwLineLen = dwClientX - dwCharX;
		dwLines = dwClientY / dwCharY;
		break;

	case WM_SETFOCUS:
		// Создаем и позиционируем каретку при получении окном фокуса 
		CreateCaret(hwndMain, (HBITMAP)1, 0, dwCharY);
		SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
		ShowCaret(hwndMain);
		break;

	case WM_KILLFOCUS:
		// Прячем и удаляем каретку при потере фокуса 
		HideCaret(hwndMain);
		DestroyCaret();
		break;

	case WM_CHAR:
		//  если символ близок к границе клиентской области, то его не рисуем
		if (cch > BUFSIZE - 5)
		{
			pchInputBuf[cch] = 0x00;
			SendMessage(hwndMain, WM_PAINT, 0, 0);
		}
		switch (wParam)
		{
		case 0x08:  // backspace 
		case 0x0A:  // linefeed 
		case 0x1B:  // escape 
			MessageBeep((UINT)-1);
			return 0;
		case 0x09:  // tab 
					// Символ tab заменяется четырьмя последовательными пробелами. 
			for (i = 0; i < 4; i++)
				SendMessage(hwndMain, WM_CHAR, 0x20, 0);
			return 0;
		case 0x0D:  // carriage return 
					// Перевод каретки на новую строку 
			pchInputBuf[cch++] = 0x0D;
			nCaretPosX = 0;
			nCaretPosY += 1;
			X += nCharWidth;
			break;
		default:    // displayable character 
			ch = (TCHAR)wParam;
			HideCaret(hwndMain);
			//  Определяем ширину и высоту символа 
			hdc = GetDC(hwndMain);
			GetCharWidth32(hdc, (UINT)wParam, (UINT)wParam, &nCharWidth);
			TextOut(hdc, nCaretPosX, nCaretPosY * dwCharY, &ch, 1);
			ReleaseDC(hwndMain, hdc);

			// Store the character in the buffer.
			pchInputBuf[cch++] = ch;

			// Изменяем позицию картеки 
			nCaretPosX += nCharWidth;
			X += nCharWidth;
			if ((DWORD)nCaretPosX > dwLineLen)
			{
				nCaretPosX = 0;
				pchInputBuf[cch++] = 0x0D;
				++nCaretPosY;
				//Y += 1;
			}
			nCurChar = cch;
			ShowCaret(hwndMain);
			break;
		}
		SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:   // LEFT ARROW 
			if (nCaretPosX > 0)
			{
				HideCaret(hwndMain);
				ch = pchInputBuf[--nCurChar];
				hdc = GetDC(hwndMain);
				GetCharWidth32(hdc, ch, ch, &nCharWidth);
				ReleaseDC(hwndMain, hdc);
				nCaretPosX = max(nCaretPosX - nCharWidth, 0);
				ShowCaret(hwndMain);
			}
			break;
		case VK_RIGHT:  // RIGHT ARROW 
			if (nCurChar < cch)
			{
				HideCaret(hwndMain);
				ch = pchInputBuf[nCurChar];
				if (ch == 0x0D)
				{
					nCaretPosX = 0;
					nCaretPosY++;
				}
				else
				{
					hdc = GetDC(hwndMain);
					nVirtKey = GetKeyState(VK_SHIFT);
					if (nVirtKey & SHIFTED)
					{
						crPrevText = SetTextColor(hdc, RGB(255, 255, 255));
						crPrevBk = SetBkColor(hdc, RGB(0, 0, 0));
						TextOut(hdc, nCaretPosX, nCaretPosY * dwCharY, &ch, 1);
						SetTextColor(hdc, crPrevText);
						SetBkColor(hdc, crPrevBk);
					}
					GetCharWidth32(hdc, ch, ch, &nCharWidth);
					ReleaseDC(hwndMain, hdc);
					nCaretPosX = nCaretPosX + nCharWidth;
				}
				nCurChar++;
				ShowCaret(hwndMain);
				break;
			}
			break;
		case VK_UP:
			if (nCaretPosY > 0)
				nCaretPosY--;
			break;
		case VK_DOWN: // DOWN ARROW 
			nCaretPosY++;
			break;
		case VK_HOME:   // HOME 
			nCaretPosX = 0;
			nCurChar = 0;
			break;
		case VK_END:																//!!!!!
			nCaretPosX = X;
			break;
		case VK_F1:																	//!!!!!
			WinExec("NotePad.exe", SW_SHOW);
			break;
		default:
			break;
		}
		SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
		break;

	case WM_PAINT:
		if (cch == 0)       // nothing in input buffer 
			break;

		hdc = BeginPaint(hwndMain, &ps);
		HideCaret(hwndMain);

		SetRect(&rc, 0, 0, dwLineLen, dwClientY);
		DrawText(hdc, pchInputBuf, -1, &rc, DT_LEFT);

		ShowCaret(hwndMain);
		EndPaint(hwndMain, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);

		// Free the input buffer.
		GlobalFree((HGLOBAL)pchInputBuf);
		UnregisterHotKey(hwndMain, 0xAAAA);
		break;

	default:
		return DefWindowProc(hwndMain, uMsg, wParam, lParam);
	}
	return NULL;
}




// Обработчик сообщений для окна "О программе".
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
