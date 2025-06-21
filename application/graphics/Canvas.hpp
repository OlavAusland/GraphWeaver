#pragma once 
#include "Graphics.hpp"
#include "OpenGL_Implementation/LineObject.hpp"
//#include <glad/glad.h>

using namespace GraphWeaver;

class Canvas
{
private:
    static LineObject line_object;
private:
    static float aspect;
    static Vec3 origo;
    static Vec3 scale;
    static Vec3 size;
public:

public:
    Canvas() = delete;


    static void Draw();
    static Vec3& GetOrigo();
    static Vec3& GetScale();
    static Vec3& GetBounds();
    static const float& GetAspect();
    static void SetOrigo(const Vec3&);
    static void SetScale(const Vec3&);
    static void SetBounds(const Vec3&);
    static void SetAspect(const float aspect);

    static void Move(const Vec3 mouse_position);
    static void Zoom(const Vec3 vel);
};
