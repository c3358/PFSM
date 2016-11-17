#include "StdAfx.h"
#include "CamException.h"
 

CamException::CamException(void)
{
}
 
CamException::~CamException(void)
{
}
 
//#pragma region //�����쳣��¼  ȫ�ִ����
 
//CStringתchar����ΪVS2005�е��ַ�����ȽϾ��ᡣ
char* CamException::CString2char(CString &str,DWORD *outCharLength) 
{ 
    int len = str.GetLength(); 
    *outCharLength = len * 2 + 1;
    char* chRtn = (char*)malloc((*outCharLength)*sizeof(char));//CString�ĳ����к�����һ������ 
    memset(chRtn, 0, *outCharLength); 
    USES_CONVERSION; 
    //strcpy((LPSTR)chRtn,OLE2A(str.LockBuffer())); 

	strcpy((LPSTR)chRtn,LPSTR(str.LockBuffer())); 
    return chRtn; 
} 

 
CString CamException::QueryExePath()
{
    TCHAR path[MAX_PATH];
    ::GetModuleFileName(NULL,path,MAX_PATH);
    CString p(path);
    CString subp;
    int nPos = p.ReverseFind('\\');
    //ASSERT(-1!=nPos);
    return p.Left(nPos+1);
}
 
 char* CamException::str2char(CString str)
{
char *ptr;
#ifdef _UNICODE
LONG len;
len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
ptr = new char[len + 1];
memset(ptr, 0, len + 1);
WideCharToMultiByte(CP_ACP, 0, str, -1, ptr, len + 1, NULL, NULL);
#else
ptr = new char[str.GetAllocLength() + 1];
sprintf(ptr, _T("%s"), str);
#endif
return ptr;
}

//����MFC�ķ�����ȡϵͳʱ�䲢д���ļ�
void CamException::WriteToFile(CString exMsg)
{
 
//#pragma region //�쳣��־
 
    SYSTEMTIME st;
    CString strTimeTag;//ʱ����
    GetLocalTime(&st);
    strTimeTag.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
 
    CString strFullExMsg;//��ʱ���ǵ��쳣��Ϣ��¼
    strFullExMsg=strTimeTag + L" # " + exMsg;
 
    DWORD dwCharLength;
   // char *pChar=CString2char(strFullExMsg,&dwCharLength);
	char *pChar=str2char(strFullExMsg);
 
//#pragma endregion
 
    CString strCurrentFolderPath=QueryExePath();    
 
 
    CFile hSaveFile;   
    hSaveFile.Open(strCurrentFolderPath+L"ErrorLog.txt",CFile::modeCreate | CFile::modeWrite |CFile::modeNoTruncate);//����һ��txt�ļ���
    hSaveFile.SeekToEnd();   //�ļ�ĩβ
 
    hSaveFile.Write(pChar,strlen(pChar));
    hSaveFile.Write("\r\n",2);
    hSaveFile.Close();
 
    free(pChar);
    pChar=NULL;
 
 
 
}
//#pragma endregion