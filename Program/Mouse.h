#pragma once
#include "Windows.h"
#include "Vec2.h"
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
	Vec2i pos;
	bool isLButtonDown = false, isRButtonDown = false;
	bool wasLButtonDown = false, wasRButtonDown = false;
	bool isInputEnabled = true;
public:
	static void EnableInput() {
		GetInstance().isInputEnabled = true;
	}
	static void DisableInput() {
		GetInstance().isInputEnabled = false;
	}
	//Returns whether the left mouse button was pressed this frame
	static bool IsLButtonPressed() {
		const Mouse& mouse = GetInstance();
		return mouse.isLButtonDown && !mouse.wasLButtonDown && mouse.isInputEnabled;
	}
	static bool IsLButtonDown() {
		const Mouse& mouse = GetInstance();
		return mouse.isLButtonDown && mouse.isInputEnabled;
	}
	static bool IsRButtonPressed() {
		const Mouse& mouse = GetInstance();
		return mouse.isRButtonDown && !mouse.wasRButtonDown && mouse.isInputEnabled;
	}
	static bool IsRButtonDown() {
		const Mouse& mouse = GetInstance();
		return mouse.isRButtonDown && mouse.isInputEnabled;
	}
	static bool IsInputEnabled() {
		return GetInstance().isInputEnabled;
	}
	static Vec2i GetMousePos() {
		return GetInstance().pos;
	}
};

