#pragma once

#define MENU_EXCUTOR_TIME_ID 293457
#define MENU_EXCUTOR_TIME_DELAY 1000
#define TOOLBAR_MENU "toolbar"
#define FUNTION_ON 1
#define FUNTION_OFF "0"

#define MENU_CTRL_ALT_DEL_SEND 	"ctrlaltdelSend"
#define MENU_CTRL_DEL_SEND 	"cteldelSend"
#define MENU_VIEWER_CLOSE 		"viewerClose"
#define MENU_DISPLAY_OPTIMIZE	"displayOptimize"
#define MENU_ONE_BY_ONE_SCALE "onebyoneScale"
#define MENU_FULLSCREEN "fullscreenMode"
#define MENU_SELECT_MONITOR "selectMonitor"
#define MENU_HIDE_BACKGROUND "hideBackground"
#define MENU_REFRESH "refreshViewer"

class CMenuExecutor
{
public:
	CMenuExecutor();
	~CMenuExecutor();

	void SetClientConnection(HINSTANCE hInst, HWND ParentWindow);
	void SetRemoteMouseDisable(bool newVale) {
		m_remote_mouse_disable = newVale;
	}

	void OnTimerEventResolve(TCHAR*iniKey);

private:
	HINSTANCE _hInstance;
	HWND _hwnd;
	bool m_remote_mouse_disable;

};

