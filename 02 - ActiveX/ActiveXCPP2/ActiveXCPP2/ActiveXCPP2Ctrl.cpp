// ActiveXCPP2Ctrl.cpp: реализация класса элемента управления ActiveX CActiveXCPP2Ctrl.

#include "stdafx.h"
#include "ActiveXCPP2.h"
#include "ActiveXCPP2Ctrl.h"
#include "ActiveXCPP2PropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CActiveXCPP2Ctrl, COleControl)

// Схема сообщений

BEGIN_MESSAGE_MAP(CActiveXCPP2Ctrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// Схема подготовки к отправке

BEGIN_DISPATCH_MAP(CActiveXCPP2Ctrl, COleControl)
	DISP_FUNCTION_ID(CActiveXCPP2Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)

	DISP_FUNCTION_ID(CActiveXCPP2Ctrl, "TestMyMethod",
		DISPID_TEST_METHOD, TestMyMethod, VT_I4, VTS_I4)


END_DISPATCH_MAP()

// Схема событий

BEGIN_EVENT_MAP(CActiveXCPP2Ctrl, COleControl)

	EVENT_CUSTOM_ID("EventHandlerTest", eventidEventHandlerTest, EventHandlerTest, VTS_BSTR VTS_BSTR VTS_I4)

END_EVENT_MAP()

// Страницы свойств

// TODO: при необходимости добавьте дополнительные страницы свойств.  Не забудьте увеличить значение счетчика.
BEGIN_PROPPAGEIDS(CActiveXCPP2Ctrl, 1)
	PROPPAGEID(CActiveXCPP2PropPage::guid)
END_PROPPAGEIDS(CActiveXCPP2Ctrl)

// Инициализировать фабрику класса и guid

IMPLEMENT_OLECREATE_EX(CActiveXCPP2Ctrl, "MFCACTIVEXCONTRO.ActiveXCPP2Ctrl.1",
	0x6a7b9efb,0x6141,0x433c,0x90,0x38,0xa5,0xfc,0x9e,0x85,0x9a,0xe6)

// Введите ИД и версию библиотеки

IMPLEMENT_OLETYPELIB(CActiveXCPP2Ctrl, _tlid, _wVerMajor, _wVerMinor)

// ИД интерфейса

const IID IID_DActiveXCPP2 = {0xb1b4b502,0xf06d,0x4d5d,{0xbb,0x11,0x7d,0xea,0x2e,0xb3,0x28,0x49}};
const IID IID_DActiveXCPP2Events = {0x0e35ce4d,0x9521,0x4c66,{0xa5,0x49,0x1e,0x3c,0xd8,0xe4,0x58,0xcd}};

// Сведения о типах элементов управления

static const DWORD _dwActiveXCPP2OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CActiveXCPP2Ctrl, IDS_ACTIVEXCPP2, _dwActiveXCPP2OleMisc)

// CActiveXCPP2Ctrl::CActiveXCPP2CtrlFactory::UpdateRegistry -
// Добавляет или удаляет записи системного реестра для CActiveXCPP2Ctrl

BOOL CActiveXCPP2Ctrl::CActiveXCPP2CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: убедитесь, что элементы управления следуют правилам модели изолированных потоков.
	// Дополнительные сведения см. в MFC TechNote 64.
	// Если элемент управления не соответствует правилам модели изоляции, то
	// необходимо модифицировать приведенный ниже код, изменив значение 6-го параметра с
	// afxRegApartmentThreading на 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_ACTIVEXCPP2,
			IDB_ACTIVEXCPP2,
			afxRegApartmentThreading,
			_dwActiveXCPP2OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CActiveXCPP2Ctrl::CActiveXCPP2Ctrl — конструктор

CActiveXCPP2Ctrl::CActiveXCPP2Ctrl()
{
	InitializeIIDs(&IID_DActiveXCPP2, &IID_DActiveXCPP2Events);
	// TODO: Инициализируйте здесь данные экземпляра элемента управления.
}

// CActiveXCPP2Ctrl::~CActiveXCPP2Ctrl — деструктор

CActiveXCPP2Ctrl::~CActiveXCPP2Ctrl()
{
	// TODO: Выполните здесь очистку данных экземпляра элемента управления.
}

// CActiveXCPP2Ctrl::OnDraw — функция рисования

void CActiveXCPP2Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO: Замените следующий код собственным кодом рисования.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CActiveXCPP2Ctrl::DoPropExchange — поддержка сохраняемости

void CActiveXCPP2Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Вызывать функции PX_ для каждого постоянного настраиваемого свойства.
}


// CActiveXCPP2Ctrl::OnResetState — сброс элемента управления к состоянию по умолчанию

void CActiveXCPP2Ctrl::OnResetState()
{
	COleControl::OnResetState();  // Сбрасывает значения по умолчанию, найденные в DoPropExchange

	// TODO: Сбросьте здесь состояние любого другого элемента управления.
}


// CActiveXCPP2Ctrl::AboutBox — отображение окна "О программе" для пользователя

void CActiveXCPP2Ctrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_ACTIVEXCPP2);
	dlgAbout.DoModal();
}

LONG CActiveXCPP2Ctrl::TestMyMethod(LONG param1)
{
	return param1*param1*3.14/2;
}

// Обработчики сообщений CActiveXCPP2Ctrl
