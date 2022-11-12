
#ifndef _EXD3D_CAMERA_HPP_
#define _EXD3D_CAMERA_HPP_

#include "exdraw.hpp"

#include "exd3d_vector.hpp"

class camera {
public:
#ifndef C3D_CAMERA_MODE

#define C3D_CAMERA_MODE

#define C3D_MODE_REAL3D 0
#define C3D_MODE_FAKE3D 1
#define C3D_MODE_SHADOW_FRONT 10
#define C3D_MODE_SHADOW_LEFT 11
#define C3D_MODE_SHADOW_TOP 12

#endif

    vector3 pos;
    double px, py, pz;
    double focalLength;

    int CameraMode;

    camera(vector3 p = vector3(), double tx = 0, double ty = 0, double fl = 10, int Mode = C3D_MODE_REAL3D)
        : pos(p), px(tx), py(ty), focalLength(fl), CameraMode(Mode)
    {
    }
    ~camera() {}

    vector2 V3DtoV2D_Real3D(vector3 a) const
    {
        double dx = cos(px) * (sin(pz) * (a.y - pos.y) + cos(pz) * (a.x - pos.x)) - sin(px) * (a.z - pos.z);
        double dy = sin(py) * (cos(px) * (a.z - pos.z) + sin(px) * (sin(pz) * (a.y - pos.y) + cos(pz) * (a.x - pos.x))) + cos(py) * (cos(pz) * (a.y - pos.y) - sin(pz) * (a.x - pos.x));
        double dz = cos(py) * (cos(px) * (a.z - pos.z) + sin(px) * (sin(pz) * (a.y - pos.y) + cos(pz) * (a.x - pos.x))) - sin(py) * (cos(pz) * (a.y - pos.y) - sin(pz) * (a.x - pos.x));
        if (dz == 0) {
            dz += 0.001;
        }
        if (dz < 0) {
            dz = 0.001;
        }
        return vector2((dx * focalLength / dz), (dy * focalLength / dz));
    }
    vector2 V3DtoV2D(vector3 a) const
    {
        vector2 res;
        switch (CameraMode) {
        case C3D_MODE_REAL3D:
            res = V3DtoV2D_Real3D(a);
            break;
        default:
            res = vector2();
            break;
        }
        return res;
    }

    double V3DPointSize(vector3 a, const double &PointSize = 2) const
    {
        double dx = cos(px) * (sin(pz) * (a.y - pos.y) + cos(pz) * (a.x - pos.x)) - sin(px) * (a.z - pos.z);
        double dy = sin(py) * (cos(px) * (a.z - pos.z) + sin(px) * (sin(pz) * (a.y - pos.y) + cos(pz) * (a.x - pos.x))) + cos(py) * (cos(pz) * (a.y - pos.y) - sin(pz) * (a.x - pos.x));
        double dz = cos(py) * (cos(px) * (a.z - pos.z) + sin(px) * (sin(pz) * (a.y - pos.y) + cos(pz) * (a.x - pos.x))) - sin(py) * (cos(pz) * (a.y - pos.y) - sin(pz) * (a.x - pos.x));
        if (dz <= 0) {
            return 0;
        }
        double dis = vector3(dx, dy, dz).length();
        if (dis > 512) {
            return 0;
        }
        return focalLength * PointSize / (dis);
    }

    inline void drawV2D(const vector2 &a, const int &color) const
    {
        drawpixel(a.x + winWidth / 2, a.y + winHeight / 2, color);
    }
    inline void drawV2DH(const vector2 &a, const double &size, const int &color) const
    {
        drawpoint(a.x + winWidth / 2, a.y + winHeight / 2, size, color);
    }
    inline void drawV2DLine(const vector2 &a, const vector2 &b, const int &color) const
    {
        drawline(a.x + winWidth / 2, a.y + winHeight / 2, b.x + winWidth / 2, b.y + winHeight / 2, color);
    }
    inline void drawV2DLineH(const vector2 &a, const vector2 &b, const double &sizef, const double &sizet, const int &color) const
    {
        drawlineH(a.x + winWidth / 2, a.y + winHeight / 2, b.x + winWidth / 2, b.y + winHeight / 2, sizef, sizet, color);
    }
    inline void drawV3D(const vector3 &a, const int &color) const
    {
        drawV2DH(V3DtoV2D(a), V3DPointSize(a, 1), color);
    }
    inline void drawV3DLine(const vector3 &a, const vector3 &b, const int &color) const
    {
#ifdef _DRAW_V3DLINE_DRIECT_
        vector3 s = b - a, t, lst;
        s.normalize();
        s /= 3;
        if (max(V3DPointSize(a), V3DPointSize(b)) == 0) {
            return;
        }
        s /= max(max(V3DPointSize(a), V3DPointSize(b)), 0.001);
        if (fabs(s.length()) < 0.01) {
            return;
        }
        t = a + s;
        lst = t;
        int cnt = 0;
        while (t != b && cnt < 10000) {
            ++cnt;
            drawV3D(t, color);
            int counter = 0;
            while (t == lst && counter < 100) {
                t += s;
                ++counter;
            }
            if (counter >= 100) {
                break;
            }
            lst = t;
        }
#else
        drawV2DLineH(V3DtoV2D(a), V3DtoV2D(b), V3DPointSize(a, 1), V3DPointSize(b, 1), color);
#endif
    }
};

#endif