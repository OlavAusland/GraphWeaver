#pragma once
#include "Utils.hpp"

namespace GraphWeaver
{

    void* GetActiveRenderer();

    void SetColor(float r, float g, float b, float a);
    Color GetActiveColor();

    void DrawPoint(double x, double y);
    void DrawPoints(void* start, int points);
    void DrawLines(void* start, int points);

    void DrawLine(const Vec3 start, const Vec3 end, const Color color = GetActiveColor());
}
