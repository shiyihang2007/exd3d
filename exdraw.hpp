
#ifndef _exdraw_hpp_
#define _exdraw_hpp_

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>

using std::max;
using std::min;

#include <conio.h>
#include <graphics.h>
#include <windows.h>

int winWidth = 480, winHeight = 360;

int drawBuf[2][1920][1080];
int freshCnt;
HWND drawArea;
RECT drawAreaRect;

void refresh()
{
    BeginBatchDraw();
    int lst = 0x000000;
    for (int i = 0; i < winWidth; ++i) {
        for (int j = 0; j < winHeight; ++j) {
            if (drawBuf[freshCnt & 1][i][j] == drawBuf[(freshCnt & 1) ^ 1][i][j]) {
                drawBuf[(freshCnt & 1) ^ 1][i][j] = 0;
                continue;
            }
            if (drawBuf[freshCnt & 1][i][j] != lst) {
                lst = drawBuf[freshCnt & 1][i][j];
            }
            putpixel(i, j, lst);
            drawBuf[(freshCnt & 1) ^ 1][i][j] = 0;
        }
    }
    EndBatchDraw();
    freshCnt ^= 1;
}
void drawpixel(int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= winWidth || y >= winHeight) {
        return;
    }
    drawBuf[freshCnt & 1][x][y] = color;
}
void drawpixelmx(int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= winWidth || y >= winHeight) {
        return;
    }
    drawBuf[freshCnt & 1][x][y] = RGB(max(GetRValue(color), GetRValue(drawBuf[freshCnt & 1][x][y])), max(GetGValue(color), GetGValue(drawBuf[freshCnt & 1][x][y])), max(GetBValue(color), GetBValue(drawBuf[freshCnt & 1][x][y])));
}
void drawpoint(int x, int y, double size, int color)
{
    if (fabs(size) < 0.01)
        return;
    if (fabs(size) < 0.5) {
        double alpha = fabs(size) * 2;
        color = RGB(GetRValue(color) * alpha, GetGValue(color) * alpha, GetBValue(color) * alpha);
    }
    size = min(size, 3.0);
    for (int i = x - size - 2; i <= x + size + 3; ++i) {
        for (int j = y - size - 2; j <= y + size + 3; ++j) {
            if (size - sqrt(pow(i - x, 2) + pow(j - y, 2)) > -0.5) {
                drawpixel(i, j, color);
            }
            // else if (size - sqrt(pow(i - x, 2) + pow(j - y, 2)) > -3) {
            //     double alpha = 2 - (sqrt(pow(i - x, 2) + pow(j - y, 2)) - size);
            //     drawpixelmx(i, j, RGB(GetRValue(color) * alpha, GetGValue(color) * alpha, GetBValue(color) * alpha));
            // }
        }
    }
}
void drawline(int fx, int fy, int tx, int ty, int color)
{
    double x = fx, y = fy;
    double scoal = fabs(1.0 / sqrt(pow(tx - fx, 2) + pow(ty - fy, 2)));
    double stepx = (tx - fx) * scoal, stepy = (ty - fy) * scoal;
    printf("<info> from (%2d, %d) to (%d, %d)\n", fx, fy, tx, ty);
    printf("<info> scoal=%1.3lf stepx=%1.3lf stepy=%1.3lf\n", scoal, stepx, stepy);
    int counter = 0;
    while ((fabs(x - tx) > 1 || fabs(y - ty) > 1) && counter < 1000) {
        drawpixel(x, y, color);
        // printf("<info> x:%2.2lf y:%2.2lf\n", x, y);
        x += stepx, y += stepy;
        ++counter;
    }
}
inline void drawlineH(int fx, int fy, int tx, int ty, int sizef, int sizet, int color)
{
    // if ((fx < 0 && tx < 0) || (fy < 0 && ty < 0) || (fx >= winWidth && tx >= winWidth) || (fy >= winHeight && ty >= winHeight)) {
    //     return;
    // }
    double x = fx, y = fy, size = sizef;
    double scoal = fabs(1.0 / sqrtl(pow(tx - fx, 2) + pow(ty - fy, 2)));
    double stepx = (tx - fx) * scoal, stepy = (ty - fy) * scoal;
    double steps = (sizet - sizef) * scoal;
    printf("<info> from (%2d, %d) to (%d, %d)\n", fx, fy, tx, ty);
    printf("<info> scoal=%1.3lf stepx=%1.3lf stepy=%1.3lf\n", scoal, stepx, stepy);
    int counter = 0;
    while ((fabs(x - tx) > 1 || fabs(y - ty) > 1) && counter < 1000) {
        drawpoint(x, y, size, color);
        // printf("<info> x:%2.2lf y:%2.2lf\n", x, y);
        x += stepx, y += stepy, size += steps;
        ++counter;
    }
}

void initExDraw()
{
#ifdef _DEBUG_
    drawArea = initgraph(winWidth, winHeight, EX_SHOWCONSOLE);
#else
    drawArea = initgraph(winWidth, winHeight);
#endif
    LOGFONT deafultFontStyle;
    gettextstyle(&deafultFontStyle);
    deafultFontStyle.lfHeight = 20;
    _tcscpy(deafultFontStyle.lfFaceName, _T("Consolas"));
    deafultFontStyle.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&deafultFontStyle);
    SetWindowText(drawArea, _T("Main"));
    GetWindowRect(drawArea, &drawAreaRect);
}
void exitExDraw()
{
    closegraph();
}

#endif