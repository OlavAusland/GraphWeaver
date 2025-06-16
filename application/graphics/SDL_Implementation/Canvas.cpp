#include "Canvas.hpp"
#include "Graphics.hpp"
#include <algorithm>

using namespace GraphWeaver;

Vec2 Canvas::origo;
Vec2 Canvas::scale;
Vec2 Canvas::size;

void Canvas::SetOrigo(const Vec2& canvas_origo)
{
    origo = canvas_origo;
}

void Canvas::SetScale(const Vec2& canvas_scale)
{
    scale = {std::max(0.1f, canvas_scale.x), std::max(0.1f, canvas_scale.y)};

}

const Vec2& Canvas::GetOrigo()
{
    return origo;
}

const Vec2& Canvas::GetScale()
{
    return scale;
}

const Vec2& Canvas::GetBounds()
{
    return size;
}

void Canvas::SetBounds(const Vec2& canvas_size)
{
    size = canvas_size;
}

void Canvas::Draw()
{
    SetColor(0, 0, 0, 255);
    // Draw main origo lines
    DrawLine({0, origo.y}, {size.x, origo.y});
    DrawLine({origo.x, 0}, {origo.x, size.y});

    SetColor(0, 0, 0, 20);

    for(float i = origo.x; i <= size.x; i++)
    {

        if((int)(origo.x - i) % (int)(scale.x * 10) == 0)
        {
            DrawLine({(float)i, 0}, {(float)i, size.y});
        }
    }

    for(float i = origo.x; i >= 0; i--)
    {
        if((int)(origo.x - i) % (int)(scale.x * 10) == 0)
        {
            DrawLine({(float)i, 0}, {(float)i, size.y});
        }
    }

    for(float i = origo.y; i >= 0; i--)
    {
        if((int)(origo.y - i) % (int)(scale.y * 10) == 0)
        {
            DrawLine({0, (float)i}, {size.x, (float)i});
        }
    }

    for(float i = origo.y; i <= size.y; i++)
    {

        if((int)(origo.y - i) % (int)(scale.y * 10) == 0)
        {
            DrawLine({0, (float)i}, {size.x, (float)i});
        }
    }
}

void Canvas::Move(const Vec2 vel)
{
    origo.x = origo.x + vel.x;
    origo.y = origo.y + vel.y;
}

void Canvas::Zoom(const Vec2 vel)
{
    scale.x = scale.x + vel.x;
    scale.y = scale.y + vel.y;
}
