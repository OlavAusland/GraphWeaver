#pragma once
#include <string>
#include "Utils.hpp"
#include "Shader.hpp"

class Shader;

class ShaderUniform
{
protected:
    std::string name;
public:
    ShaderUniform(const std::string& name);

    virtual void Bind(Shader* shader) = 0;
    const std::string& GetName() const;
};

template <typename T>
class Uniform : public ShaderUniform
{
private:
    T data;
public:
    Uniform(const std::string& name, T data) : ShaderUniform(name), data(data) {}
    void Bind(Shader* shader) override;
};


template<>
void Uniform<float*>::Bind(Shader* shader);

template<>
void Uniform<GraphWeaver::Vec2*>::Bind(Shader* shader);

template<>
void Uniform<GraphWeaver::Vec3*>::Bind(Shader* shader);

template<>
void Uniform<GraphWeaver::Vec4*>::Bind(Shader* shader);

template<>
void Uniform<glm::mat4>::Bind(Shader* shader);


