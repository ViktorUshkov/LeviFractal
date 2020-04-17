#include "calc.h"

point_t get_point(line_t line) {
	point_t new_point;
	new_point.x = (line.beg.x + line.end.x) / 2 - (line.end.y - line.beg.y) / 2;
	new_point.y = (line.beg.y + line.end.y) / 2 + (line.end.x - line.beg.x) / 2;
	return new_point;
}