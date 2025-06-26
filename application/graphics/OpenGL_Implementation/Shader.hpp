#pragma once
#include <string>
#include <sys/stat.h>
#include <unordered_map>
#include <glad/glad.h>
#include "Utils.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderUniform.hpp"
#include <vector>
#include <memory>

class ShaderUniform;

class Shader
{
private:
public:
    unsigned int shader_program;

    unsigned int vertex_shader;
    unsigned int fragment_shader;

    //std::vector<std::unique_ptr<ShaderUniform>> uniforms;
    std::unordered_map<std::string, std::unique_ptr<ShaderUniform>> uniforms;
    std::unordered_map<std::string, unsigned int> uniform_map;
private:
public:
    struct stat vertex_info;
    std::string vertex_file;

    struct stat fragment_info;
    std::string fragment_file;
public:
    Shader(std::string vertex_file, std::string fragment_file);
    ~Shader();
    Shader(const Shader& other)
    {
        vertex_file = other.vertex_file;
        fragment_file = other.fragment_file;
    }

    void SetUniform(std::unique_ptr<ShaderUniform> uniform);
    void Reload();
    void SetActive();
    unsigned int GetProgram() const;
    
    void SetUniform1f(std::string name, float value);
    void SetUniform2f(std::string name, GraphWeaver::Vec2 value);
    void SetUniform3f(std::string name, GraphWeaver::Vec3 value);
    void SetUniform4f(std::string name, GraphWeaver::Vec4 value);
    void SetUniformMatrix4fv(std::string name, glm::mat4 value);

    Shader& operator=(const Shader&);
private:
    bool HasChanged();
    int Compile(const std::string& file, unsigned int shader);
    int CreateProgram();
};
