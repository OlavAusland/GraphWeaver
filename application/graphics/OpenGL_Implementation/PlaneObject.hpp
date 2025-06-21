#pragma once
#include "DrawObject.hpp"

class PlaneObject : public DrawObject
{
public:
    PlaneObject();

    void Draw() override;
    void Clear() override;
    void AddPoint(GraphWeaver::Vec3 point) override;
};
