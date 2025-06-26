#include "ShaderUniform.hpp"

ShaderUniform::ShaderUniform(const std::string& name)
    : name(name)
{
}

const std::string& ShaderUniform::GetName() const
{
    return name;
}


template<>
void Uniform<float*>::Bind(Shader* shader)
{
    if(!shader || !data) { return; }

    shader->SetUniform1f(name, *data);
}

template<>
void Uniform<GraphWeaver::Vec2*>::Bind(Shader* shader)
{
    if(!shader || !data) { return; }

    shader->SetUniform2f(name, *data);
}

template<>
void Uniform<GraphWeaver::Vec3*>::Bind(Shader* shader)
{
    if(!shader || !data) { return; }

    shader->SetUniform3f(name, *data);
}

template<>
void Uniform<GraphWeaver::Vec4*>::Bind(Shader* shader)
{
    if(!shader || !data) { return; }

    shader->SetUniform4f(name, *data);
}

template<>
void Uniform<glm::mat4>::Bind(Shader* shader)
{
    if(!shader) { return; }

    shader->SetUniformMatrix4fv(name, data);
}
