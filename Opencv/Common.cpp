#include "Common.hpp"

struct EnumWindowsArg {
	HWND hwnd;
	LPCWSTR class_name;
};

void ConvertDpiRect(RECT* rect, int current_dpi){
	rect->left = MulDiv(rect->left, 100, current_dpi);
	rect->top = MulDiv(rect->top, 100, current_dpi);
	rect->right = MulDiv(rect->right, 100, current_dpi);
	rect->bottom = MulDiv(rect->bottom, 100, current_dpi);
}

BOOL CALLBACK EnumChildWindowProc(HWND hwnd, LPARAM lparam){
	/*-----初始化-----*/
	WCHAR class_name[MAX_CLASS_NAME];
	const auto arg = reinterpret_cast<EnumWindowsArg*>(lparam);
	GetClassNameW(hwnd, class_name, MAX_CLASS_NAME);

	/*-----子窗口-----*/
	if (!lstrcmpW(class_name, arg->class_name)) {
		arg->hwnd = hwnd;
		return false;
	}
	return true;
}

BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lparam){
	/*-----初始化-----*/
	WCHAR class_name[MAX_CLASS_NAME];
	const auto arg = reinterpret_cast<EnumWindowsArg*>(lparam);
	GetClassNameW(hwnd, class_name, MAX_CLASS_NAME);

	/*-----父窗口-----*/
	if (!lstrcmpW(class_name, arg->class_name)){
		arg->hwnd = hwnd;
		return false;
	}

	/*-----子窗口-----*/
	EnumChildWindows(hwnd, EnumChildWindowProc, lparam);
	return arg->hwnd == nullptr ? true : false;
}

HWND GetWindowHWNDByClass(LPCWSTR class_name){
	EnumWindowsArg arg{ nullptr, class_name };
	EnumWindows(EnumWindowProc, reinterpret_cast<LPARAM>(&arg));
	return arg.hwnd;
}