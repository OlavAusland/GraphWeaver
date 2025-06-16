#pragma once
#include <vector>
#include "Utils.hpp"

class DrawObject
{
protected:
    unsigned int VBO;
    unsigned int VAO;
    std::vector<GraphWeaver::Vec3> points;
public:
    virtual void Draw() = 0;
    virtual void Clear() = 0;
    virtual void AddPoint(GraphWeaver::Vec3 point) = 0;
    std::vector<GraphWeaver::Vec3>& GetPoints();
};
