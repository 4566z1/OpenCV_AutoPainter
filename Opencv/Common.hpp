#pragma once
#ifndef  _COMMON_
#define _COMMON_

#include <string_view>
#include <Windows.h>
using std::string_view;

/*
 * ����ӦDPI
 */
extern void ConvertDpiRect(RECT* rect, int current_dpi);

/*
 * ������ȡ���ھ��
 */
extern HWND GetWindowHWNDByClass(LPCWSTR class_name);

#endif