#pragma once

#include "stdafx.h"
class CamException
{
public:
    CamException(void);
    ~CamException(void);
private:
   static  char* str2char(CString str);
    static char* CString2char(CString &str,DWORD *outCharLength);//CStringתchar����ΪVS2005�е��ַ�����ȽϾ���
    static CString QueryExePath();//��õ�ǰEXE�����·��
     
public:
    static void WriteToFile(CString exMsg);//����MFC�ķ�����ȡϵͳʱ�䡡����д���ļ�
};