#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <glad/glad.h>

#include "Shader.hpp"
#include "glm/gtc/matrix_transform.hpp"

Shader::Shader(std::string vertex_file, std::string fragment_file)
    :   vertex_shader(glCreateShader(GL_VERTEX_SHADER)),
        fragment_shader(glCreateShader(GL_FRAGMENT_SHADER)),
        vertex_file(vertex_file),
        fragment_file(fragment_file)
{
    if(stat(vertex_file.c_str(), &vertex_info) != 0)
    {
        printf("[ERROR] Failed to read vertex file (stat)!\n");
    }


    if(stat(fragment_file.c_str(), &fragment_info) != 0)
    {
        printf("[ERROR] Failed to read fragmnet file (stat)!\n");
    }
    
    if(Compile(vertex_file, vertex_shader) && Compile(fragment_file, fragment_shader))
        CreateProgram();
}

bool Shader::HasChanged()
{
    struct stat new_info;

    if(stat(vertex_file.c_str(), &new_info) == 0)
    {
        if(vertex_info.st_mtim.tv_sec != new_info.st_mtim.tv_sec)
        {
            vertex_info = new_info;
            return true;
        }
    }

    if(stat(fragment_file.c_str(), &new_info) == 0)
    {
        if(fragment_info.st_mtim.tv_sec != new_info.st_mtim.tv_sec)
        {
            fragment_info = new_info;
            return true;
        }
    }

    return false;
}

void Shader::Reload()
{
    if(HasChanged())
    {
        printf("[INFO] Shader has changed, reloading!\n");

        if(Compile(vertex_file, vertex_shader) && Compile(fragment_file, fragment_shader))
            CreateProgram();
    }
}

int Shader::Compile(const std::string& file, unsigned int shader)
{
    int success;
    char infoLog[512];

    std::ifstream filestream(file);
    std::string buffer{std::istreambuf_iterator<char>(filestream), std::istreambuf_iterator<char>()};
    const char* source = buffer.c_str();

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        printf("[ERROR] Failed to compile shader: %s", infoLog);
    }

    return success;
}

int Shader::CreateProgram()
{
    int success;
    char infoLog[512];

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
        printf("[ERROR] Failed to create program: %s", infoLog);
    }

    return success;
}

void Shader::SetActive()
{
    glUseProgram(shader_program);
}

unsigned int Shader::GetProgram() const
{
    return shader_program;
}

void Shader::SetUniform3f(std::string name, GraphWeaver::Vec3 value)
{
    if(uniform_map.find(name) == uniform_map.end())
    {
        uniform_map[name] = glGetUniformLocation(shader_program, name.c_str());
        
    }

    glUniform3f(uniform_map[name], value.x, value.y, value.z);
}

void Shader::SetUniform4f(std::string name, GraphWeaver::Vec4 value)
{
    if(uniform_map.find(name) == uniform_map.end())
    {
        uniform_map[name] = glGetUniformLocation(shader_program, name.c_str());
        
    }

    glUniform4f(uniform_map[name], value.x, value.y, value.z, value.w);
}

void Shader::SetUniformMatrix4fv(std::string name, glm::mat4 value)
{
    if(uniform_map.find(name) == uniform_map.end())
    {
        uniform_map[name] = glGetUniformLocation(shader_program, name.c_str());
        
    }

    glUniformMatrix4fv(uniform_map[name], 1, GL_FALSE, &value[0][0]);
}


Shader::~Shader()
{
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(shader_program);
}
