#include "Canvas.hpp"
#include "Graphics.hpp"
#include <algorithm>
#include "LineObject.hpp"
#include "PlaneObject.hpp"
#include <glad/glad.h>
#include <stdio.h>
#include "ShaderManager.hpp"
#include "Utils.hpp"
#include "Camera.hpp"

using namespace GraphWeaver;

Vec3 Canvas::origo;
Vec3 Canvas::scale;
Vec2 Canvas::size;
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

Vec2& Canvas::GetBounds()
{
    return size;
}

const float& Canvas::GetAspect()
{
    return aspect;
}

void Canvas::SetBounds(const Vec2& canvas_size)
{
    size = canvas_size;
}

void Canvas::SetAspect(const float value)
{
    aspect = value;
}

void Canvas::Draw()
{

    static PlaneObject plane = ShaderManager::GetShader("canvas");
    static Camera& camera = GetActiveCamera();

    static Vec4 color{0.3, 0.3, 0.3, 1.0};
    static Vec3 old_scale = scale;
    static Vec2 spacing = {1, 1};

    glm::mat4 model(1.0f);
    model = glm::translate(model, {origo.x, origo.y, origo.z});

    plane.shader.SetUniform(std::make_unique<Uniform<Vec4*>>("u_color", &color));
    plane.shader.SetUniform(std::make_unique<Uniform<Vec3*>>("u_scale", &scale));
    plane.shader.SetUniform(std::make_unique<Uniform<Vec2*>>("u_resolution", &size));
    plane.shader.SetUniform(std::make_unique<Uniform<Vec2*>>("u_spacing", &spacing));
    plane.shader.SetUniform(std::make_unique<Uniform<glm::mat4>>("u_MVP", camera() * camera.view * model));

    // ugly code should refactor

    if((scale.x - old_scale.x) > old_scale.x * 2)
    {
        old_scale.x = scale.x;
        spacing.x += spacing.x;
        spacing.x = std::max(spacing.x, 1.0f);
    }
    else if((scale.x) < old_scale.x / 2)
    {
        old_scale.x = scale.x;
        spacing.x /= 2;
        spacing.x = std::max(spacing.x, 1.0f);
    }

    if((scale.y - old_scale.y) > old_scale.y * 2)
    {
        old_scale.y = scale.y;
        spacing.y += spacing.y;
        spacing.y = std::max(spacing.y, 1.0f);
    }
    else if((scale.y) < old_scale.y / 2)
    {
        old_scale.y = scale.y;
        spacing.y /= 2;
        spacing.y = std::max(spacing.y, 1.0f);
    }


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
