
// InkPictureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "InkPicture.h"
#include "InkPictureDlg.h"
#include "afxdialogex.h"

#include <WTypes.h>
#include <msinkaut.h>
#include <msinkaut_i.c>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInkPictureDlg 对话框



CInkPictureDlg::CInkPictureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInkPictureDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInkPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInkPictureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CInkPictureDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInkPictureDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInkPictureDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON8, &CInkPictureDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CInkPictureDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, &CInkPictureDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CInkPictureDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CInkPictureDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CInkPictureDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CInkPictureDlg 消息处理程序

BOOL CInkPictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//启用点擦除模式
	setPointEraseMode(true);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInkPictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CInkPictureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CInkPictureDlg::setEditingMode(short mode)
{
	CComPtr<IInkPicture> ip;

	// Retrieve the DISPID by using a COM Client for the InkPicture  // control.
	DISPID dispid = 0;
	OLECHAR FAR* szMember = OLESTR("EditingMode");
	ip.CoCreateInstance(CLSID_InkPicture);
	ip->GetIDsOfNames(IID_IInkPicture, &szMember, 1,
		LOCALE_SYSTEM_DEFAULT, &dispid);

	// Retrieve the CWnd for the InkPicture Control.
	CWnd* pInkWnd = NULL;
	pInkWnd = this->GetDlgItem(IDC_INKPICTURE1);

	pInkWnd->SetProperty(dispid, VT_I2, mode);
	ip.Release();
}


void CInkPictureDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	setEditingMode(InkOverlayEditingMode::IOEM_Ink);
}


void CInkPictureDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	setEditingMode(InkOverlayEditingMode::IOEM_Delete);
}


void CInkPictureDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	setEditingMode(InkOverlayEditingMode::IOEM_Select);
}

//点擦除模式
void CInkPictureDlg::setPointEraseMode(bool setToPointMode)
{
	CComPtr<IInkPicture> ip;

	// Retrieve dispid.
	DISPID dispid = 0;
	OLECHAR FAR* szMember = OLESTR("EraserMode");
	ip.CoCreateInstance(CLSID_InkPicture);
	ip->GetIDsOfNames(IID_IInkPicture, &szMember, 1,
		LOCALE_SYSTEM_DEFAULT, &dispid);

	// Retrieve the CWnd for the InkPicture control.
	CWnd* pInkWnd = NULL;
	pInkWnd = this->GetDlgItem(IDC_INKPICTURE1);

	// Toggle the property based on the point mode.
	if (setToPointMode){
		pInkWnd->SetProperty(dispid, VT_I2,
			InkOverlayEraserMode::IOERM_PointErase);
	}
	else{
		pInkWnd->SetProperty(dispid, VT_I2,
			InkOverlayEraserMode::IOERM_StrokeErase);
	}

	ip.Release();
}


void CInkPictureDlg::setStrokeThickness(bool isThick)
{
	CComPtr<IInkPicture> ip;
	CComPtr<IInkDrawingAttributes> spIInkDrawAttrs = NULL;

	// Set to thick or thin based on bool.
	// 50 is the default width.
	// 250 is a good thickness.
	float newWidth = isThick ? 250 : 50;

	DISPID dispid = 0;
	OLECHAR FAR* szMember = OLESTR("DefaultDrawingAttributes");

	ip.CoCreateInstance(CLSID_InkPicture);
	ip->GetIDsOfNames(IID_IInkPicture, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);

	CWnd* pInkWnd = NULL;
	pInkWnd = this->GetDlgItem(IDC_INKPICTURE1);

	// Retrieve the drawing attributes interface.
	pInkWnd->GetProperty(dispid, VT_UNKNOWN, &spIInkDrawAttrs);

	// Now use the interface to set the width.
	//spIInkDrawAttrs->put_Color(RGB(255, 0, 0));
	spIInkDrawAttrs->put_Width(newWidth);

	// Now pass the interface back to set the drawing attributes.
	pInkWnd->SetProperty(dispid, VT_DISPATCH, spIInkDrawAttrs);

	// Free.
	spIInkDrawAttrs.Release();
	ip.Release();
}


void CInkPictureDlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	this->setStrokeThickness(false);
}


void CInkPictureDlg::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码
	this->setStrokeThickness(true);
}


void CInkPictureDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	COLORREF color = RGB(255, 0, 0);
	setColor(color);
}


void CInkPictureDlg::setColor(long NewColor)
{
	CComPtr<IInkPicture> ip;
	CComPtr<IInkDrawingAttributes> spIInkDrawAttrs = NULL;

	DISPID dispid = 0;
	OLECHAR FAR* szMember = OLESTR("DefaultDrawingAttributes");

	ip.CoCreateInstance(CLSID_InkPicture);
	ip->GetIDsOfNames(IID_IInkPicture, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);

	CWnd* pInkWnd = NULL;
	pInkWnd = this->GetDlgItem(IDC_INKPICTURE1);

	// Retrieve the drawing attributes interface.
	pInkWnd->GetProperty(dispid, VT_UNKNOWN, &spIInkDrawAttrs);

	// Now use the interface to set the width.
	spIInkDrawAttrs->put_Color(NewColor);

	// Now pass the interface back to set the drawing attributes.
	pInkWnd->SetProperty(dispid, VT_DISPATCH, spIInkDrawAttrs);

	// Free.
	spIInkDrawAttrs.Release();
	ip.Release();
}


void CInkPictureDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	COLORREF color = RGB(0, 0, 255);
	setColor(color);
}


void CInkPictureDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	COLORREF color = RGB(0, 255, 0);
	setColor(color);
}


void CInkPictureDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	COLORREF color = RGB(0, 0, 0);
	setColor(color);
}
