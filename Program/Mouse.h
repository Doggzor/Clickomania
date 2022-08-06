#pragma once
#include "Windows.h"
#include "Vector2i.h"
class Mouse
{
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	friend int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int);
private:
	Mouse() {}
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	~Mouse() {}
	static Mouse& GetInstance() {
		static Mouse mouse;
		return mouse;
	}
	Vector2i pos;
	bool isLButtonDown = false;
	bool wasLButtonDown = false;
public:
	//Returns whether the left mouse button was pressed this frame
	static bool IsLButtonPressed() {
		const Mouse& mouse = GetInstance();
		return mouse.isLButtonDown && !mouse.wasLButtonDown;
	}
	static Vector2i GetMousePos() {
		return GetInstance().pos;
	}
};

