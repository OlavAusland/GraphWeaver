#include "ShaderManager.hpp"
#include "Shader.hpp"

std::unordered_map<std::string, Shader> ShaderManager::shaders;

void ShaderManager::AddShader(std::string name, std::string vertex, std::string fragment)
{
    shaders.emplace(name, Shader(vertex, fragment));
}

Shader ShaderManager::GetShader(std::string name)
{
    return shaders.find(name)->second;
}

void ShaderManager::Initialize()
{
    shaders = {
        {"default", Shader("/home/olav/Documents/C++/GraphWeaver/shaders/default_vertex_shader.glsl",
                           "/home/olav/Documents/C++/GraphWeaver/shaders/default_fragment_shader.glsl")},
        
        {"grid",    Shader("/home/olav/Documents/C++/GraphWeaver/shaders/grid_vertex.glsl",
                           "/home/olav/Documents/C++/GraphWeaver/shaders/grid_fragment.glsl")},

        {"point",   Shader("/home/olav/Documents/C++/GraphWeaver/shaders/point_vertex.glsl",
                           "/home/olav/Documents/C++/GraphWeaver/shaders/point_fragment.glsl")}
        };
}

