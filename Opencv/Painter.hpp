#pragma once
#ifndef _PAINTER_
#define _PAINTER_

#include <Windows.h>
#include <string>
using std::string_view;
using std::string;

namespace PAINTER
{
	class Painter{
	private:
		string filename;
		LPCWSTR class_name;
		HWND window_hwnd;

		bool UpdateHandle();
	public:
		Painter(string_view filename, LPCWSTR class_name) : filename(filename), class_name(class_name){}
		~Painter() = default;

		bool Paint();
	};
}

#endif 