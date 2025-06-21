#include "Canvas.hpp"
#include "Graphics.hpp"
#include <algorithm>
#include "LineObject.hpp"
#include "PlaneObject.hpp"
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

const float& Canvas::GetAspect()
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
    static PlaneObject plane;
    plane.Clear();

    plane.AddPoint({-origo.x + scale.x * aspect / 2.0f, -origo.y + scale.y / 2,  0});
    plane.AddPoint({-origo.x + scale.x * aspect / 2.0f, -origo.y - scale.y / 2,  0});
    plane.AddPoint({-origo.x - scale.x * aspect / 2.0f, -origo.y + scale.y / 2,  0});
    plane.AddPoint({-origo.x - scale.x * aspect / 2.0f, -origo.y - scale.y / 2,  0});

    plane.Draw();

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
