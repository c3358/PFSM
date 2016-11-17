
// TrayIconDemoDlg.h : header file
//
#include "TrayIcon.h"
#include "CamException.h"
#include <string>
#include <Dbt.h>
#pragma once

using namespace std;

typedef struct _loginState
{
	bool islogin;
	bool isOffMode;
	std::string s_username;
	std::string s_password;

}LOGIN_STATE;

// CTrayIconDemoDlg dialog
class CTrayIconDemoDlg : public CDialogEx
{
public:
	CTrayIconDemoDlg(CWnd* pParent = NULL);	// standard constructor
	~CTrayIconDemoDlg();	// standard destroyor
    LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);// Dialog Data

	enum { IDD = IDD_TRAYICONDEMO_DIALOG };
	void DoSomethingBeforeMsgLoop();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
    afx_msg void OnSysCommand(UINT nID,LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL PreTranslateMessage(MSG* pMsg);//��ֹENTER,ESC�����˳�����

	DECLARE_MESSAGE_MAP()

private:
    void ToTray();
	void RemoveTray();

	CString QueryExePath();//��ȡ��ǰ���������ļ���·��

	char* str2char(CString str);

protected:
	HICON m_hIcon;
	
private:  

	CStatusBar  m_StausBar;//״̬��

	CamException exception;//�쳣��¼��־

	CString strCurrentFolderPath;//Ŀǰ����·��

	PROCESS_INFORMATION pi;
public:
	BOOL m_TrayFlag;//if the tray icon has been displayed before,the value is true,and vice versa.
	CTrayIcon m_TrayIcon;

	CString m_username;
	CString m_password;

	static LOGIN_STATE loginState;

	afx_msg void OnTraymenuOpenapp();//�������溯��
    afx_msg void OnTraymenuExit();//�˳�������
	afx_msg void OnBnClickedLogin();//���뺯��
	afx_msg void OnBnClickedLogout();//�ǳ�����
	afx_msg void OnTraymenuSettings();
};

