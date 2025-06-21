#pragma once
#include <vector>
#include "Utils.hpp"
#include "Shader.hpp"
#include "Script.hpp"

class DrawObject
{
public:
    Shader shader;
protected:
    GraphWeaver::Color color;

    unsigned int VBO;
    unsigned int VAO;
    std::vector<GraphWeaver::Vec3> points;

    Script* master;
public:
    DrawObject();
    virtual void Draw() = 0;
    virtual void Clear() = 0;
    virtual void AddPoint(GraphWeaver::Vec3 point) = 0;

    void SetScriptOwner(Script* script);
    void SetActiveShader(std::string id);
    void SetColor(float r, float g, float b, float a);
    std::vector<GraphWeaver::Vec3>& GetPoints();
};
