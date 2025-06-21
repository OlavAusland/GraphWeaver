#include "DrawObject.hpp"
#include "ShaderManager.hpp"
#include <string>

void DrawObject::SetColor(float r, float g, float b, float a)
{
    color = {r, g, b, a};
}

DrawObject::DrawObject()
:   shader("/home/olav/Documents/C++/GraphWeaver/shaders/default_vertex_shader.glsl",
                           "/home/olav/Documents/C++/GraphWeaver/shaders/default_fragment_shader.glsl"),
    color{1.0, 1.0, 1.0, 1.0}
{
}


void DrawObject::SetScriptOwner(Script* script)
{
    master = script;
}

void DrawObject::SetActiveShader(std::string id)
{
}

std::vector<GraphWeaver::Vec3>& DrawObject::GetPoints()
{
    return points;
}

