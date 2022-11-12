
// #define _DEBUG_

/*使用准确的3D算法*/
#define _DRAW_V3DLINE_DRIECT_

/*EXD3D & EasyX绘图库*/
#include "Includes\exd3d.hpp"

int main()
{
    /*加载绘图窗口*/
    initExDraw();

    /*变量*/
    /*是否继续消息循环*/
    bool ProcessGoOn = 1;
    /*计时器*/
    DWORD timeCnt = 0, lstTimeCnt = timeCnt;
    DWORD nowTime = GetTickCount(), lstTime = nowTime;
    /*帧率暂存*/
    int freshPerSecond = 0;
    /*是否锁定鼠标*/
    int MouseLock = 0;
    /*窗口中心*/
    int winX = 0, winY = 0;

    /*常数*/
    /*旋转模数*/
    const double roMod = acos(-1) * 2;
    /*弧度转角度*/
    const double rBase = 180 / acos(-1);

    /*自定义常数*/
    /* fpsUpdateRate 默认 1
     * 帧率更新频率
     * 0.0~120
     * 越小更新越慢 但越准确
     */
    const double fpsUpdateRate = 1;
    /* MouseMoveRate 默认 100
     * 鼠标灵敏度
     * 10.0~1000.0
     * 越小越灵敏 不建议过小
     */
    const double MouseMoveRate = 100;

    /* 设置主摄像机属性
     * int focalLength   焦距 1~512    默认 128
     * vector3 pos       坐标 all      默认 vector3(0, 0, 0)
     * double px, py, pz 旋转 0~2*PI   默认 0 0 0
     * int CameraMode    模式 C3D_MODE 默认 C3D_MODE_REAL3D
     */
    mainCamera.focalLength = 128;
    mainCamera.pos = vector3(0, 0, -25);

    /*正方体模型*/
    V3DCube Cube(10);

    while (ProcessGoOn) {
        /*更新计时器*/
        ++timeCnt;
        nowTime = GetTickCount();
        /*帧率显示*/
        if (nowTime - lstTime >= (long unsigned int)(1000 / fpsUpdateRate)) {
            freshPerSecond = (timeCnt - lstTimeCnt) * fpsUpdateRate;
            lstTimeCnt = timeCnt;
            lstTime = nowTime;
            TCHAR fpsText[20];
            _stprintf(fpsText, _T("FPS: %3d"), freshPerSecond);
            outtextxy(5, 5, fpsText);
        }
        /*摄像机位置显示*/
        if (timeCnt % 10 == 0) {
            TCHAR focalText[20];
            _stprintf(focalText, _T("FocalLength: %3.3lf"), mainCamera.focalLength);
            outtextxy(5, 25, focalText);
            TCHAR XYZText[45];
            _stprintf(XYZText, _T("(%3.2lf,%3.2lf,%3.2lf)"), mainCamera.pos.x, mainCamera.pos.y, mainCamera.pos.z);
            outtextxy(5, 45, XYZText);
            TCHAR RXYText[45];
            _stprintf(RXYText, _T("(%3.2lf,%3.2lf)"), mainCamera.px * rBase, mainCamera.py * rBase);
            outtextxy(5, 65, RXYText);
        }
        // printf("%.2lf %.2lf\n", sin(mainCamera.px), cos(mainCamera.px));
        /*处理消息*/
        ExMessage nowMsg;
        /*只获取鼠标消息与按键消息*/
        while (peekmessage(&nowMsg, EX_MOUSE | EX_KEY)) {
            /*枚举消息类型*/
            switch (nowMsg.message) {
            /*鼠标左键*/
            case WM_LBUTTONDOWN:
                if (MouseLock == 0) {
                    MouseLock = 1;
                    GetWindowRect(drawArea, &drawAreaRect);
                    winX = (drawAreaRect.right + drawAreaRect.left) / 2;
                    winY = (drawAreaRect.top + drawAreaRect.bottom) / 2;
                    SetCursorPos(winX, winY);
                }
                break;
            /*鼠标移动*/
            case WM_MOUSEMOVE:
                if (MouseLock) {
                    mainCamera.px += (nowMsg.x + drawAreaRect.left + 3 - winX) / MouseMoveRate;
                    mainCamera.py -= (nowMsg.y + drawAreaRect.top + 26 - winY) / MouseMoveRate;
                    mainCamera.px = int((mainCamera.px + roMod) * 100) % (int)(roMod * 100) / 100.0;
                    mainCamera.py = int((mainCamera.py + roMod) * 100) % (int)(roMod * 100) / 100.0;
                    SetCursorPos(winX, winY);
                }
                break;
            /*鼠标滚轮*/
            case WM_MOUSEWHEEL:
                mainCamera.focalLength += nowMsg.wheel / 120;
                break;

            /*键盘按下*/
            case WM_KEYDOWN:
                switch (nowMsg.vkcode) {
                case 'W':
                    mainCamera.pos.x += sin(mainCamera.px);
                    mainCamera.pos.z += cos(mainCamera.px);
                    break;
                case 'S':
                    mainCamera.pos.x -= sin(mainCamera.px);
                    mainCamera.pos.z -= cos(mainCamera.px);
                    break;
                case 'A':
                    mainCamera.pos.x -= cos(mainCamera.px);
                    mainCamera.pos.z += sin(mainCamera.px);
                    break;
                case 'D':
                    mainCamera.pos.x += cos(mainCamera.px);
                    mainCamera.pos.z -= sin(mainCamera.px);
                    break;
                case 'Q':
                    break;
                case 'E':
                    MouseLock = 0;
                    break;
                case ' ':
                    mainCamera.pos.y--;
                    break;
                case VK_SHIFT:
                    mainCamera.pos.y++;
                    break;
                case VK_ESCAPE:
                    ProcessGoOn = 0;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        /*显示图像*/
        Cube.display(mainCamera);
        refresh();
        /*休眠*/
        Sleep(2);
    }
    exitExDraw();
    return 0;
}
