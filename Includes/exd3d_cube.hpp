#ifndef _EXD3D_CUBE_HPP_
#define _EXD3D_CUBE_HPP_

#include "exd3d_camera.hpp"
#include "exd3d_vector.hpp"

#include <vector>

class V3DCube {
public:
    std::vector<vector3> nodeTable;
    std::vector<std::pair<int, int>> edgeTable;

    int color;

    V3DCube(int x = 10, int c = 0xffffff) : color(c)
    {
        nodeTable = {
            vector3(+x, +x, +x),
            vector3(+x, +x, -x),
            vector3(-x, +x, +x),
            vector3(-x, +x, -x),
            vector3(+x, -x, +x),
            vector3(+x, -x, -x),
            vector3(-x, -x, +x),
            vector3(-x, -x, -x)};
        edgeTable = {
            std::pair<int, int>(0, 1),
            std::pair<int, int>(0, 2),
            std::pair<int, int>(0, 4),
            std::pair<int, int>(1, 3),
            std::pair<int, int>(1, 5),
            std::pair<int, int>(2, 3),
            std::pair<int, int>(2, 6),
            std::pair<int, int>(3, 7),
            std::pair<int, int>(4, 5),
            std::pair<int, int>(4, 6),
            std::pair<int, int>(5, 7),
            std::pair<int, int>(6, 7)};
    }
    ~V3DCube() {}

    /*显示*/
    void display(camera &Camera) const
    {
        for (auto w : edgeTable) {
            Camera.drawV3DLine(nodeTable[w.first], nodeTable[w.second], color);
        }
        for (auto w : nodeTable) {
            Camera.drawV3D(w, color);
        }
    }
};

#endif
