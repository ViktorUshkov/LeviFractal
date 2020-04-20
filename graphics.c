#include <windows.h>
#include "graphics.h"
#include "calc.h"

void Draw(HDC hdc, int itr, line_t base) {
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	if (itr == 0) {
		MoveToEx(hdc, base.beg.x, base.beg.y, NULL);
		LineTo(hdc, base.end.x, base.end.y);
	}
	else {
		point_t new_point = { 0,0 };
		line_t next_line1 = { {0,0}, {0,0} };
		line_t next_line2 = { {0,0}, {0,0} };
		new_point = get_point(base);
		next_line1.beg = base.beg;
		next_line1.end = new_point;
		next_line2.beg = new_point;
		next_line2.end = base.end;
		Draw(hdc, itr - 1, next_line1);
		Draw(hdc, itr - 1, next_line2);
	}
	DeleteObject(hPen);
}

point_t get_point(line_t line) {
	point_t new_point;
	new_point.x = (line.beg.x + line.end.x) / 2 - (line.end.y - line.beg.y) / 2;
	new_point.y = (line.beg.y + line.end.y) / 2 + (line.end.x - line.beg.x) / 2;
	return new_point;
}
