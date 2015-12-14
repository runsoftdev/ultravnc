#include "stdhdrs.h"
#include "res\\resource.h"
#include "MenuExecutor.h"
#include "Exception.h"

CMenuExecutor::CMenuExecutor()
{
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
void CMenuExecutor::OnTimerEventResolve(TCHAR*iniKey)
{
	if (_hwnd == NULL || _hInstance == NULL || iniKey == NULL) {
		return; 
	}

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
	
	int isSendCtrlAltDel = GetPrivateProfileInt(iniKey, MENU_CTRL_ALT_DEL_SEND, 0, szFileName);
	int isClose = GetPrivateProfileInt(iniKey, MENU_VIEWER_CLOSE, 0, szFileName);
	int isDisplayOptimize = GetPrivateProfileInt(iniKey, MENU_DISPLAY_OPTIMIZE, 0, szFileName);
	int isOneByOneScale = GetPrivateProfileInt(iniKey, MENU_ONE_BY_ONE_SCALE, 0, szFileName);
	int isFullScreen = GetPrivateProfileInt(iniKey, MENU_FULLSCREEN, 0, szFileName);
	int isSelectMonitor = GetPrivateProfileInt(iniKey, MENU_SELECT_MONITOR, 0, szFileName);
	int isHideBackground = GetPrivateProfileInt(iniKey, MENU_HIDE_BACKGROUND, 0, szFileName);
	int isRefresh = GetPrivateProfileInt(iniKey, MENU_REFRESH, 0, szFileName);
	int isStartButton = GetPrivateProfileInt(iniKey, MENU_CTRL_DEL_SEND, 0, szFileName);
	try {
		if (isStartButton) {
			SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_CONN_CTLESC, (LPARAM)0);
			WritePrivateProfileString(iniKey, MENU_CTRL_DEL_SEND, FUNTION_OFF, szFileName);
			OutputDebugString("isStartButton on");
		}
		if (isSendCtrlAltDel) {
			SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_CONN_CTLALTDEL, (LPARAM)0);
			WritePrivateProfileString(iniKey, MENU_CTRL_ALT_DEL_SEND, FUNTION_OFF, szFileName);
			OutputDebugString("isSendCtrlAltDel on");
		}
		if (isClose) {
			SendMessage(_hwnd, WM_CLOSE, (WPARAM)0, (LPARAM)0);
			WritePrivateProfileString(iniKey, MENU_VIEWER_CLOSE, FUNTION_OFF, szFileName);
			OutputDebugString("isClose on");
		}
		if (isDisplayOptimize) {			
			
			WritePrivateProfileString(iniKey, MENU_DISPLAY_OPTIMIZE, FUNTION_OFF, szFileName);
			SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)8899, (LPARAM)0);
			OutputDebugString("isDisplayOptimize on");
		}
		if (isOneByOneScale) {
			
			WritePrivateProfileString(iniKey, MENU_ONE_BY_ONE_SCALE, FUNTION_OFF, szFileName);
			SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_NORMALSCREEN2, (LPARAM)0);
			OutputDebugString("isOneByOneScale on");
		}
		if (isFullScreen) {
			SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_FULLSCREEN, (LPARAM)0);
			WritePrivateProfileString(iniKey, MENU_FULLSCREEN, FUNTION_OFF, szFileName);
			OutputDebugString("isFullScreen on");
		}
		if (isSelectMonitor) {
			SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_DESKTOP, (LPARAM)0);
			WritePrivateProfileString(iniKey, MENU_SELECT_MONITOR, FUNTION_OFF, szFileName);
			OutputDebugString("isSelectMonitor on");
		}
		if (isHideBackground) {
			if (m_remote_mouse_disable)
			{
				m_remote_mouse_disable = false;
				SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_INPUT, (LPARAM)0);
				SendMessage(_hwnd, WM_SIZE, (WPARAM)ID_DINPUT, (LPARAM)0);
			}
			else
			{
				m_remote_mouse_disable = true;
				SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_DINPUT, (LPARAM)0);
				SendMessage(_hwnd, WM_SIZE, (WPARAM)ID_DINPUT, (LPARAM)0);
			}
			OutputDebugString("isHideBackground on");
			WritePrivateProfileString(iniKey, MENU_HIDE_BACKGROUND, FUNTION_OFF, szFileName);
		}
		if (isRefresh) {
			SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_REQUEST_REFRESH, (LPARAM)0);
			WritePrivateProfileString(iniKey, MENU_REFRESH, FUNTION_OFF, szFileName);

			OutputDebugString("isRefresh on");
		}
	}
	catch (...) {

	}
	
}

void CMenuExecutor::ConnectFailed(TCHAR*iniKey)
{
	if (_hwnd == NULL || _hInstance == NULL) {
		return;
	}

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

	WritePrivateProfileString(iniKey, MENU_CONNECT_TRY, FUNTION_OFF, szFileName);
}