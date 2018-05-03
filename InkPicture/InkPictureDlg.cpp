
// InkPictureDlg.cpp : ʵ���ļ�
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


// CInkPictureDlg �Ի���



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


// CInkPictureDlg ��Ϣ�������

BOOL CInkPictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//���õ����ģʽ
	setPointEraseMode(true);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CInkPictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	setEditingMode(InkOverlayEditingMode::IOEM_Ink);
}


void CInkPictureDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	setEditingMode(InkOverlayEditingMode::IOEM_Delete);
}


void CInkPictureDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	setEditingMode(InkOverlayEditingMode::IOEM_Select);
}

//�����ģʽ
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->setStrokeThickness(false);
}


void CInkPictureDlg::OnBnClickedButton9()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->setStrokeThickness(true);
}


void CInkPictureDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	COLORREF color = RGB(0, 0, 255);
	setColor(color);
}


void CInkPictureDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	COLORREF color = RGB(0, 255, 0);
	setColor(color);
}


void CInkPictureDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	COLORREF color = RGB(0, 0, 0);
	setColor(color);
}
