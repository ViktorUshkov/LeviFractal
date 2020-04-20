#pragma once
#include <windows.h>

#define MIN 0
#define MAX 15

typedef struct
{
    int x, y;
} point_t;

typedef struct
{
    point_t beg, end;
} line_t;

void Draw (HDC hdc, int itr, line_t base);
point_t get_point(line_t line);
