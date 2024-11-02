#pragma once
#ifndef  _COMMON_
#define _COMMON_

#include <string_view>
#include <Windows.h>
using std::string_view;

/*
 * 自适应DPI
 */
extern void ConvertDpiRect(RECT* rect, int current_dpi);

/*
 * 类名获取窗口句柄
 */
extern HWND GetWindowHWNDByClass(LPCWSTR class_name);

#endif