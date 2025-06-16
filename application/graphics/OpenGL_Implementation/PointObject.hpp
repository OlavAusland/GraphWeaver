#pragma once
#include "DrawObject.hpp"

class PointObject : public DrawObject
{
public:
    PointObject();

    void Draw() override;
    void Clear() override;

    void AddPoint(GraphWeaver::Vec3 point) override;
};
