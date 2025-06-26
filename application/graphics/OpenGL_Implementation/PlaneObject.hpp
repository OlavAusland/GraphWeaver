#pragma once
#include "DrawObject.hpp"

class PlaneObject : public DrawObject
{
public:
    PlaneObject();
    PlaneObject(Shader shader);

    void Draw() override;
    void Clear() override;
    void AddPoint(GraphWeaver::Vec3 point) override;
};
