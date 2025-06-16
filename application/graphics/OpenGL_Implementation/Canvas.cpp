#include "Canvas.hpp"
#include "Graphics.hpp"
#include <algorithm>
#include "LineObject.hpp"
#include <glad/glad.h>
#include <stdio.h>

using namespace GraphWeaver;

Vec3 Canvas::origo;
Vec3 Canvas::scale;
Vec3 Canvas::size;
float Canvas::aspect;


void Canvas::SetOrigo(const Vec3& canvas_origo)
{
    origo = canvas_origo;
}

void Canvas::SetScale(const Vec3& canvas_scale)
{
    scale = {std::max(0.1f, canvas_scale.x), std::max(0.1f, canvas_scale.y)};

}

Vec3& Canvas::GetOrigo()
{
    return origo;
}

Vec3& Canvas::GetScale()
{
    return scale;
}

Vec3& Canvas::GetBounds()
{
    return size;
}

float Canvas::GetAspect()
{
    return aspect;
}

void Canvas::SetBounds(const Vec3& canvas_size)
{
    size = canvas_size;
}

void Canvas::SetAspect(const float value)
{
    aspect = value;
}

void Canvas::Draw()
{
    static LineObject line_object(GL_LINES);
    line_object.Clear();
    //SetColor(0, 0, 0, 255);
    // Draw main origo lines
    line_object.AddPoint({0, origo.y, 0});
    line_object.AddPoint({scale.x * aspect, origo.y, 0});

    line_object.AddPoint({origo.x, 0, 0});
    line_object.AddPoint({origo.x, scale.y, 0});

    line_object.Draw();
}

void Canvas::Move(const Vec3 vel)
{
    origo.x = origo.x + vel.x;
    origo.y = origo.y + vel.y;
}

void Canvas::Zoom(const Vec3 vel)
{
    scale.x = scale.x + vel.x;
    scale.y = scale.y + vel.y;
}
