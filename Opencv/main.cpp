#include "Painter.hpp"
using PAINTER::Painter;

int main() {
	Painter painter("test2.jpg", L"MSPaintView");
	painter.Paint();
	return 1;
}