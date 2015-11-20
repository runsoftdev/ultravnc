#include "stdhdrs.h"
#include "res\\resource.h"
#include "MenuExecutor.h"


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
void CMenuExecutor::OnTimerEventResolve()
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
		strcat(szFileName, "\\runSupportToolbar.ini");
	}

	int isSendCtrlAltDel = GetPrivateProfileInt(TOOLBAR_MENU, MENU_CTRL_ALT_DEL_SEND, 0, szFileName);
	int isClose = GetPrivateProfileInt(TOOLBAR_MENU, MENU_VIEWER_CLOSE, 0, szFileName);
	int isDisplayOptimize = GetPrivateProfileInt(TOOLBAR_MENU, MENU_DISPLAY_OPTIMIZE, 0, szFileName);
	int isOneByOneScale = GetPrivateProfileInt(TOOLBAR_MENU, MENU_ONE_BY_ONE_SCALE, 0, szFileName);
	int isFullScreen = GetPrivateProfileInt(TOOLBAR_MENU, MENU_FULLSCREEN, 0, szFileName);
	int isSelectMonitor = GetPrivateProfileInt(TOOLBAR_MENU, MENU_SELECT_MONITOR, 0, szFileName);
	int isHideBackground = GetPrivateProfileInt(TOOLBAR_MENU, MENU_HIDE_BACKGROUND, 0, szFileName);
	int isRefresh = GetPrivateProfileInt(TOOLBAR_MENU, MENU_REFRESH, 0, szFileName);
	int isStartButton = GetPrivateProfileInt(TOOLBAR_MENU, MENU_CTRL_DEL_SEND, 0, szFileName);
	
	if (isStartButton) {
		SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_CONN_CTLESC, (LPARAM)0);
		WritePrivateProfileString(TOOLBAR_MENU, MENU_CTRL_DEL_SEND, FUNTION_OFF, szFileName);
		OutputDebugString("isStartButton on");
	}
	if (isSendCtrlAltDel) {
		SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_CONN_CTLALTDEL, (LPARAM)0);
		WritePrivateProfileString(TOOLBAR_MENU, MENU_CTRL_ALT_DEL_SEND, FUNTION_OFF, szFileName);
		OutputDebugString("isSendCtrlAltDel on");
	}
	if (isClose) {
		SendMessage(_hwnd, WM_CLOSE, (WPARAM)0, (LPARAM)0);
		WritePrivateProfileString(TOOLBAR_MENU, MENU_VIEWER_CLOSE, FUNTION_OFF, szFileName);
		OutputDebugString("isClose on");
	}
	if (isDisplayOptimize) {
		WritePrivateProfileString(TOOLBAR_MENU, MENU_DISPLAY_OPTIMIZE, FUNTION_OFF, szFileName);
		OutputDebugString("isDisplayOptimize on");
	}
	if (isOneByOneScale) {
		WritePrivateProfileString(TOOLBAR_MENU, MENU_ONE_BY_ONE_SCALE, FUNTION_OFF, szFileName);
		OutputDebugString("isOneByOneScale on");
	}
	if (isFullScreen) {
		SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_FULLSCREEN, (LPARAM)0);
		WritePrivateProfileString(TOOLBAR_MENU, MENU_FULLSCREEN, FUNTION_OFF, szFileName);
		OutputDebugString("isFullScreen on");
	}
	if (isSelectMonitor) {
		SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_DESKTOP, (LPARAM)0);
		WritePrivateProfileString(TOOLBAR_MENU, MENU_SELECT_MONITOR, FUNTION_OFF, szFileName);
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
		WritePrivateProfileString(TOOLBAR_MENU, MENU_HIDE_BACKGROUND, FUNTION_OFF, szFileName);
	}
	if (isRefresh) {
		SendMessage(_hwnd, WM_SYSCOMMAND, (WPARAM)ID_REQUEST_REFRESH, (LPARAM)0);
		WritePrivateProfileString(TOOLBAR_MENU, MENU_REFRESH, FUNTION_OFF, szFileName);

		OutputDebugString("isRefresh on");
	}
}
