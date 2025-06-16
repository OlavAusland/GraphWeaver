#pragma once
#include "DrawObject.hpp"

class LineObject : public DrawObject
{
private:
    int draw_mode;
public:
    LineObject(int draw_mode);

    void Draw() override;
    void Clear() override;
    void AddPoint(GraphWeaver::Vec3 point) override;
    //void AddLine(GraphWeaver::Vec3 start, GraphWeaver::Vec3 end);
};
