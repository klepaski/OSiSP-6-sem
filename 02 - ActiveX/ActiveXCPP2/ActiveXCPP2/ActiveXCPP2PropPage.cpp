// ActiveXCPP2PropPage.cpp: реализация класса страницы свойств CActiveXCPP2PropPage.

#include "stdafx.h"
#include "ActiveXCPP2.h"
#include "ActiveXCPP2PropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CActiveXCPP2PropPage, COlePropertyPage)

// Схема сообщений

BEGIN_MESSAGE_MAP(CActiveXCPP2PropPage, COlePropertyPage)
END_MESSAGE_MAP()

// Инициализировать фабрика класса и guid

IMPLEMENT_OLECREATE_EX(CActiveXCPP2PropPage, "MFCACTIVEXCONT.ActiveXCPP2PropPage.1",
	0x4c2859e8,0xb9fe,0x41c0,0xab,0x5d,0x66,0xc3,0xd0,0x61,0xb4,0x2a)

// CActiveXCPP2PropPage::CActiveXCPP2PropPageFactory::UpdateRegistry -
// Добавляет или удаляет записи системного реестра для CActiveXCPP2PropPage

BOOL CActiveXCPP2PropPage::CActiveXCPP2PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ACTIVEXCPP2_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// CActiveXCPP2PropPage::CActiveXCPP2PropPage — конструктор

CActiveXCPP2PropPage::CActiveXCPP2PropPage() :
	COlePropertyPage(IDD, IDS_ACTIVEXCPP2_PPG_CAPTION)
{
}

// CActiveXCPP2PropPage::DoDataExchange — перемещение данных между страницей и свойствами

void CActiveXCPP2PropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// Обработчики сообщений CActiveXCPP2PropPage
