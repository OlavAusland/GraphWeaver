#include "Graphics.hpp"
#include "DrawManager.hpp"
#include <stdio.h>

void GraphWeaver::SetColor(float r, float g, float b, float a = 1)
{
    DrawManager::SetColor(r, g, b, a);
}

GraphWeaver::Color GraphWeaver::GetActiveColor()
{
    return DrawManager::GetActiveColor();
}

void* GraphWeaver::GetActiveRenderer()
{
    return nullptr;
}

void GraphWeaver::DrawPoint(double x, double y)
{
}

void GraphWeaver::DrawPoints(void* start, int points)
{
}

void GraphWeaver::DrawLines(void* start, int points)
{
}

void GraphWeaver::DrawLine(const Vec3 start, const Vec3 end, const Color color)
{
}

