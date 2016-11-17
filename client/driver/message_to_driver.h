#pragma once

#include <Windows.h>
#include <stdio.h>
#include <fltuser.h>
#include <FltUserStructures.h>
#include <Winuser.h>
#include <winbase.h>
#include <stdlib.h>
#include <shellapi.h>

#pragma comment(lib, "FltLib.lib")

#define MINISPY_NAME      L"MiniSpy"

#define MINISPY_PORT_NAME    L"\\MiniSpyPort"

#define _CMD_PATH 296

typedef enum _MY_COMMAND 
{
	ADD_PROTECTED_PATH,
	DEL_PROTECTED_PATH,
	START_SERVICE,
	STOP_SERVICE
} MY_COMMAND;

typedef struct _INPUT_BUFFER
{
	MY_COMMAND command;
	WCHAR protectedPath[_CMD_PATH];
	WCHAR fileType[_CMD_PATH];
}INPUT_BUFFER, *PINPUT_BUFFER;

void flush_desktop()
{
	wchar_t user[100];
	wchar_t desk_path[200] = {0};
	int len;
	
	HWND desktop = GetDesktopWindow();
	
	len = GetEnvironmentVariable(L"USERNAME", user, 100);
	
	user[len] = 0;
	
	wcscat( desk_path, L"C:\\Users\\" );
	
	wcscat(desk_path, user);
	
	wcscat( desk_path, L"\\Desktop" );
	
	//ShellExecute(desktop, L"open", desk_path, NULL, NULL, SW_SHOW);

	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
}

void start_service()
{
	HANDLE port = INVALID_HANDLE_VALUE;
	DWORD result;
	INPUT_BUFFER input;
	HRESULT hResult = S_OK;

	hResult = FilterConnectCommunicationPort( MINISPY_PORT_NAME,
		0,
		NULL,
		0,
		NULL,
		&port );

	if (IS_ERROR( hResult )) 
	{
		goto Exit;
	}

	ZeroMemory(&input, sizeof(INPUT_BUFFER));

	input.command = START_SERVICE;
	wcscpy(input.protectedPath, L"");
	wcscpy(input.fileType, L"");

	FilterSendMessage(port,
			&input,
			sizeof(INPUT_BUFFER),
			NULL,
			0,
			&result);

Exit:
	if (INVALID_HANDLE_VALUE != port) 
	{
		CloseHandle( port );
	}
	flush_desktop();
}

void stop_service()
{
	HANDLE port = INVALID_HANDLE_VALUE;
	DWORD result;
	INPUT_BUFFER input;
	HRESULT hResult = S_OK;

	hResult = FilterConnectCommunicationPort( MINISPY_PORT_NAME,
		0,
		NULL,
		0,
		NULL,
		&port );

	if (IS_ERROR( hResult )) 
	{
		goto Exit;
	}

	ZeroMemory(&input, sizeof(INPUT_BUFFER));

	input.command = STOP_SERVICE;
	wcscpy(input.protectedPath, L"");
	wcscpy(input.fileType, L"");

	FilterSendMessage(port,
			&input,
			sizeof(INPUT_BUFFER),
			NULL,
			0,
			&result);

Exit:
	if (INVALID_HANDLE_VALUE != port) 
	{
		CloseHandle( port );
	}
	flush_desktop();
}

VOID MyAddProtectPath(WCHAR *path, WCHAR *fileType)
{
	HANDLE port = INVALID_HANDLE_VALUE;
	DWORD result;
	INPUT_BUFFER input;
	HRESULT hResult = S_OK;

	hResult = FilterConnectCommunicationPort( MINISPY_PORT_NAME,
		0,
		NULL,
		0,
		NULL,
		&port );

	if (IS_ERROR( hResult )) 
	{
		goto Exit;
	}

	ZeroMemory(&input, sizeof(INPUT_BUFFER));

	input.command = ADD_PROTECTED_PATH;
	wcscpy(input.protectedPath, path);
	wcscpy(input.fileType, fileType);


	//���� ADD_PROTECTED_PATH���׼�������������ͨ��
	FilterSendMessage(port,
		&input,
		sizeof(INPUT_BUFFER),
		NULL,
		0,
		&result);

Exit:
	if (INVALID_HANDLE_VALUE != port) 
	{
		CloseHandle( port );
	}
	flush_desktop();
}


VOID MyDelProtectPath(WCHAR *path, WCHAR *fileType)
{
	HANDLE port = INVALID_HANDLE_VALUE;
	DWORD result;
	INPUT_BUFFER input;
	HRESULT hResult = S_OK;

	hResult = FilterConnectCommunicationPort( MINISPY_PORT_NAME,
		0,
		NULL,
		0,
		NULL,
		&port );

	if (IS_ERROR( hResult )) 
	{
		goto Exit;
	}

	ZeroMemory(&input, sizeof(INPUT_BUFFER));

	input.command = DEL_PROTECTED_PATH;
	wcscpy(input.protectedPath, path);
	wcscpy(input.fileType, fileType);


	//���� DEL_PROTECTED_PATH���׼�������������ͨ��
	FilterSendMessage(port,
		&input,
		sizeof(INPUT_BUFFER),
		NULL,
		0,
		&result);

Exit:
	if (INVALID_HANDLE_VALUE != port) 
	{
		CloseHandle( port );
	}
	flush_desktop();
}
