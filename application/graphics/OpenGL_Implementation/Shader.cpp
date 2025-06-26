#include <GLES2/gl2.h>
#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <glad/glad.h>

#include "Shader.hpp"
#include "Utils.hpp"
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
    else
    {
        printf("[ ERROR ] Failed to compile shader\n");
    }
}

Shader& Shader::operator=(const Shader& other)
{
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(shader_program);

    vertex_file = other.vertex_file;
    fragment_file = other.fragment_file;
    vertex_info = other.vertex_info;
    fragment_info = other.fragment_info;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    if(Compile(vertex_file, vertex_shader) && Compile(fragment_file, fragment_shader))
        CreateProgram();
    else
    {
        printf("[ ERROR ] Failed to compile shader\n");
    }

    uniform_map.clear();

    return *this;
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

void Shader::SetUniform(std::unique_ptr<ShaderUniform> uniform)
{
    uniforms[uniform->GetName()] = std::move(uniform);
}

void Shader::Reload()
{
    if(HasChanged())
    {
        printf("[INFO] Shader has changed, reloading!\n");

        if(shader_program != 0)
        {
            glDeleteProgram(shader_program);
            shader_program = 0;
            glDeleteShader(vertex_shader);
            vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glDeleteShader(fragment_shader);
            fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        }

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
    if(shader_program == 0)
    {
        printf("Failed to create program\n");
    }

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
        printf("[ERROR] Failed to create program: %s", infoLog);
    }

    uniform_map.clear();

    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);

    return success;
}

void Shader::SetActive()
{
    glUseProgram(shader_program);

    for(auto const& uniform : uniforms)
    {
        uniform.second->Bind(this);
    }
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

void Shader::SetUniform1f(std::string name, float value)
{
    if(uniform_map.find(name) == uniform_map.end())
    {
        uniform_map[name] = glGetUniformLocation(shader_program, name.c_str());
    }

    glUniform1f(uniform_map[name], value);
}

void Shader::SetUniform2f(std::string name, GraphWeaver::Vec2 value)
{
    if(uniform_map.find(name) == uniform_map.end())
    {
        uniform_map[name] = glGetUniformLocation(shader_program, name.c_str());
    }

    glUniform2f(uniform_map[name], value.x, value.y);
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
    printf("[ INFO ] Deleting shader!\n");
    glDeleteProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
