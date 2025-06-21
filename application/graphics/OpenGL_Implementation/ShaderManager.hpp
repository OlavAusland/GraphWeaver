#pragma once
#include "Shader.hpp"
#include <vector>
#include <unordered_map>

class ShaderManager
{
private:
    static std::unordered_map<std::string, Shader> shaders;
public:
    static void AddShader(std::string name, std::string vertex, std::string fragment);
    static Shader GetShader(std::string name);
    static void Initialize();
};
