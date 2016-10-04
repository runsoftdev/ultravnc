#include "stdhdrs.h"
#include "res\\resource.h"
#include "MenuExecutor.h"
#include "Exception.h"
#include "ClientConnection.h"

CMenuExecutor::CMenuExecutor()
{
	m_isClosed = false;
}


CMenuExecutor::~CMenuExecutor()
{
}

//------------------------------------------------------------------------------
void CMenuExecutor::SetClientConnection(HINSTANCE hInst, HWND ParentWindow)
{
	_hInstance = hInst;
	_hwnd = ParentWindow;
}


//------------------------------------------------------------------------------
void CMenuExecutor::OnTimerEventResolve(ClientConnection*pClient)
{
	if (_hwnd == NULL || _hInstance == NULL) {
		return; 
	}

	char szFileName[MAX_PATH], caption[MAX_PATH] = { 0, };
	if (GetModuleFileNameA(NULL, szFileName, MAX_PATH))
	{
		char* p = strrchr(szFileName, '\\');
		if (p == NULL) return;
		*p = '\0';
#ifdef _RUNVIEW
		strcat(szFileName, "\\runViewerToolbar.ini");
#else
		strcat(szFileName, "\\runSupportToolbar.ini");
#endif
	}
	
	int isSendCtrlAltDel = GetPrivateProfileInt(m_iniKey, MENU_CTRL_ALT_DEL_SEND, 0, szFileName);
	int isClose = GetPrivateProfileInt(m_iniKey, MENU_VIEWER_CLOSE, 0, szFileName);
	int isDisplayOptimize = GetPrivateProfileInt(m_iniKey, MENU_DISPLAY_OPTIMIZE, 0, szFileName);
	int isOneByOneScale = GetPrivateProfileInt(m_iniKey, MENU_ONE_BY_ONE_SCALE, 0, szFileName);
	int isFullScreen = GetPrivateProfileInt(m_iniKey, MENU_FULLSCREEN, 0, szFileName);
	int isSelectMonitor = GetPrivateProfileInt(m_iniKey, MENU_SELECT_MONITOR, 0, szFileName);
	int isHideBackground = GetPrivateProfileInt(m_iniKey, MENU_HIDE_BACKGROUND, 0, szFileName);
	int isRefresh = GetPrivateProfileInt(m_iniKey, MENU_REFRESH, 0, szFileName);
	int isStartButton = GetPrivateProfileInt(m_iniKey, MENU_CTRL_DEL_SEND, 0, szFileName);
	int isViewOnlyButton = GetPrivateProfileInt(m_iniKey, MENU_VIEWONLY_ONOFF, 0, szFileName);
	int isServerDisableViewOnlyButton = GetPrivateProfileInt(m_iniKey, MENU_SERVERINPUT_DISABLE_ONOFF, 0, szFileName);
	int isServerEnableViewOnlyButton = GetPrivateProfileInt(m_iniKey, MENU_SERVERINPUT_ENABLE_ONOFF, 0, szFileName);
	int isServerScaleOnOffButton = GetPrivateProfileInt(m_iniKey, MENU_SERVERSCALE_ENABLE_ONOFF, 0, szFileName);
	
	GetPrivateProfileString(m_iniKey, CHANGE_CAPTION, "", caption, MAX_PATH, szFileName);	
	
	try {
		if (strlen(caption) > 0) {
			
			std::string search = m_iniKey;
			std::string replace = caption;
			std::string subject = pClient->m_desktopName;

			size_t pos = 0;
			while ((pos = subject.find(search, pos)) != std::string::npos) {
				subject.replace(pos, search.length(), replace);
				pos += replace.length();
			}

			SetWindowText(pClient->m_hwndMain, subject.c_str());			
			WritePrivateProfileString(m_iniKey, CHANGE_CAPTION, "", szFileName);
			strcpy(m_iniKey, caption);
		}
		
		if (isStartButton) {
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_CONN_CTLESC, (LPARAM)0);
			WritePrivateProfileString(m_iniKey, MENU_CTRL_DEL_SEND, FUNTION_OFF, szFileName);
			OutputDebugString("isStartButton on\n");
		}
		if (isSendCtrlAltDel) {
			
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_CONN_CTLALTDEL, (LPARAM)0);
			WritePrivateProfileString(m_iniKey, MENU_CTRL_ALT_DEL_SEND, FUNTION_OFF, szFileName);
			OutputDebugString("isSendCtrlAltDel on\n");
		}

		if (isServerScaleOnOffButton) {
			pClient->m_opts.m_Directx = !pClient->m_opts.m_Directx;
			pClient->OldEncodingStatusWindow = -2;
			pClient->m_pendingFormatChange = true;
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)WM_SIZE, (LPARAM)0);
			SendMessage(pClient->m_hwndMain, WM_SIZE, (WPARAM)ID_DINPUT, (LPARAM)0);
			
			WritePrivateProfileString(m_iniKey, MENU_SERVERSCALE_ENABLE_ONOFF, FUNTION_OFF, szFileName);
			OutputDebugString("isServerScaleOnOffButton on\n");
		}		

		if (isClose) {
			m_isClosed = true;
			KillTimer(_hwnd, MENU_EXCUTOR_TIME_ID);
			KillTimer(pClient->m_hwndMain, MENU_EXCUTOR_TIME_ID);
			
			//pClient->KillThread();
			pClient->m_autoReconnect == 0;
						
			WritePrivateProfileString(m_iniKey, MENU_VIEWER_CLOSE, FUNTION_OFF, szFileName);			
			WritePrivateProfileString(m_iniKey, MENU_FULLSCREEN_ONOFF, FUNTION_OFF, szFileName);
			OutputDebugString("isClose on\n");
			
			Sleep(500);
						
			SendMessage(pClient->m_hwndMain, WM_CLOSE, (WPARAM)0, (LPARAM)10);
			
			Sleep(500);
			
			PostQuitMessage(0);
		}

		if (isDisplayOptimize) {			
			WritePrivateProfileString(m_iniKey, MENU_DISPLAY_OPTIMIZE, FUNTION_OFF, szFileName);
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)8899, (LPARAM)0);
			OutputDebugString("isDisplayOptimize on\n");
		}
		
		if (isOneByOneScale) {			
			WritePrivateProfileString(m_iniKey, MENU_ONE_BY_ONE_SCALE, FUNTION_OFF, szFileName);
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_NORMALSCREEN2, (LPARAM)0);
			OutputDebugString("isOneByOneScale on\n");
		}
		
		if (isFullScreen) {
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_FULLSCREEN, (LPARAM)0);
			WritePrivateProfileString(m_iniKey, MENU_FULLSCREEN, FUNTION_OFF, szFileName);
			OutputDebugString("isFullScreen on\n");
		}
		
		if (isSelectMonitor) {
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_DESKTOP, (LPARAM)0);
			WritePrivateProfileString(m_iniKey, MENU_SELECT_MONITOR, FUNTION_OFF, szFileName);
			OutputDebugString("isSelectMonitor on\n");
		}

		if (isViewOnlyButton) {
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_VIEWONLYTOGGLE, (LPARAM)0);
			WritePrivateProfileString(m_iniKey, MENU_VIEWONLY_ONOFF, FUNTION_OFF, szFileName);
			OutputDebugString("isViewOnlyButton on\n");
		}

		if (isServerDisableViewOnlyButton) {
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_DINPUT, (LPARAM)0);
			WritePrivateProfileString(m_iniKey, MENU_SERVERINPUT_DISABLE_ONOFF, FUNTION_OFF, szFileName);
			OutputDebugString("isServerViewOnlyButton on\n");
		}

		if (isServerEnableViewOnlyButton) {
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_INPUT, (LPARAM)0);
			WritePrivateProfileString(m_iniKey, MENU_SERVERINPUT_ENABLE_ONOFF, FUNTION_OFF, szFileName);
			OutputDebugString("isServerViewOnlyButton on\n");
		}

		if (isHideBackground) {
			if (m_remote_mouse_disable)
			{
				m_remote_mouse_disable = false;
				SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_INPUT, (LPARAM)0);
				SendMessage(pClient->m_hwndMain, WM_SIZE, (WPARAM)ID_DINPUT, (LPARAM)0);
			}
			else
			{
				m_remote_mouse_disable = true;
				SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_DINPUT, (LPARAM)0);
				SendMessage(pClient->m_hwndMain, WM_SIZE, (WPARAM)ID_DINPUT, (LPARAM)0);
			}
			OutputDebugString("isHideBackground on\n");
			WritePrivateProfileString(m_iniKey, MENU_HIDE_BACKGROUND, FUNTION_OFF, szFileName);
		}

		if (isRefresh) {
			SendMessage(pClient->m_hwndMain, WM_SYSCOMMAND, (WPARAM)ID_REQUEST_REFRESH, (LPARAM)0);
			WritePrivateProfileString(m_iniKey, MENU_REFRESH, FUNTION_OFF, szFileName);

			OutputDebugString("isRefresh on\n");
		}
	}
	catch (Exception&e) {

	}
	catch (...) {

	}	
}

//------------------------------------------------------------------------------
void CMenuExecutor::ConnectFailed()
{
	try {
		char szFileName[MAX_PATH];
		if (GetModuleFileNameA(NULL, szFileName, MAX_PATH))
		{
			char* p = strrchr(szFileName, '\\');
			if (p == NULL) return;
			*p = '\0';
#ifdef _RUNVIEW
			strcat(szFileName, "\\runViewerToolbar.ini");
#else
			strcat(szFileName, "\\runSupportToolbar.ini");
#endif
		}

		WritePrivateProfileString(m_iniKey, MENU_CONNECT_TRY, FUNTION_OFF, szFileName);
		WritePrivateProfileString(m_iniKey, MENU_FULLSCREEN_ONOFF, FUNTION_OFF, szFileName);
	}
	catch (Exception&e) {

	}
	catch (...) {

	}
}

//------------------------------------------------------------------------------
void CMenuExecutor::Connected()
{
	try {
		char szFileName[MAX_PATH];
		if (GetModuleFileNameA(NULL, szFileName, MAX_PATH))
		{
			char* p = strrchr(szFileName, '\\');
			if (p == NULL) return;
			*p = '\0';
#ifdef _RUNVIEW
			strcat(szFileName, "\\runViewerToolbar.ini");
#else
			strcat(szFileName, "\\runSupportToolbar.ini");
#endif
		}

		WritePrivateProfileString(m_iniKey, CONNECTED_VNC, FUNTION_ON, szFileName);
		
	}
	catch (Exception&e) {

	}
	catch (...) {

	}
}

//------------------------------------------------------------------------------
void CMenuExecutor::FullScreenMode(bool isFullScreen)
{
	try {
		char szFileName[MAX_PATH];
		if (GetModuleFileNameA(NULL, szFileName, MAX_PATH))
		{
			char* p = strrchr(szFileName, '\\');
			if (p == NULL) return;
			*p = '\0';
#ifdef _RUNVIEW
			strcat(szFileName, "\\runViewerToolbar.ini");
#else
			strcat(szFileName, "\\runSupportToolbar.ini");
#endif
		}

		//OutputDebugString(isFullScreen ? "MENU_FULLSCREEN_ON\n" : "MENU_FULLSCREEN_ OFF\n");

		WritePrivateProfileString(m_iniKey, MENU_FULLSCREEN_ONOFF, isFullScreen ? FUNTION_ON : FUNTION_OFF, szFileName);
	}
	catch (Exception&e) {

	}
	catch (...) {

	}
}