#pragma once
#include <string>
#include <sys/stat.h>
#include <unordered_map>
#include <glad/glad.h>
#include "Utils.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
private:
    unsigned int shader_program;

    unsigned int vertex_shader;
    unsigned int fragment_shader;

    std::unordered_map<std::string, unsigned int> uniform_map;
private:
    struct stat vertex_info;
    std::string vertex_file;

    struct stat fragment_info;
    std::string fragment_file;
public:
    Shader(std::string vertex_file, std::string fragment_file);
    ~Shader();

    void Reload();
    void SetActive();
    unsigned int GetProgram() const;
    
    void SetUniform3f(std::string name, GraphWeaver::Vec3 value);
    void SetUniform4f(std::string name, GraphWeaver::Vec4 value);
    void SetUniformMatrix4fv(std::string name, glm::mat4 value);
private:
    bool HasChanged();
    int Compile(const std::string& file, unsigned int shader);
    int CreateProgram();
};
