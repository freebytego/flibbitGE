#pragma once
#include <Windows.h>
#include <windowsx.h>

class Window {
public:
	Window();
	~Window();

	bool InitializeWindow(int scrWidth, int scrHeight);
	bool ReleaseWindow();
	bool Cycle();
	bool IsRunning();

	int GetScreenSize(int axis);

	virtual void onCreate();
	virtual void onExit();
	virtual void onCycle();

protected:
	HWND m_hWnd;
	bool m_isRunning;

private:
	int m_screenWidth;
	int m_screenHeight;
};