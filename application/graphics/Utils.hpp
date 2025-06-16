#pragma once

namespace GraphWeaver
{

    #pragma pack(push, 1)
    typedef struct 
    {
        float x, y;
    } Vec2;
    #pragma pack(pop)

    #pragma pack(push, 1)
    typedef struct 
    {
        float x, y, z;
    } Vec3;
    #pragma pack(pop)

    #pragma pack(push, 1)
    typedef struct
    {
        float x, y, z, w;
    } Vec4;
    #pragma pack(pop)

    typedef struct
    {
        float r, g, b, a;
    } Color;
}

