#include "Entity.hpp"
#include "Scripting/PyScript.hpp"
#include <memory>

Entity::Entity(std::string name)
    : name(name), data(nullptr), data_size(0), m_is_active(true)
{
}

const std::string& Entity::GetName() const
{
    return name;
}

void Entity::SetName(char* new_name)
{
    name = new_name;
}

void Entity::AddScript(std::string file)
{
    scripts.push_back(std::make_unique<PyScript>(file));
}

const bool Entity::IsActive() const
{
    return m_is_active;
}

bool* Entity::IsActivePtr()
{
    return &m_is_active;
}

void Entity::ExecuteAll()
{
    for(auto const& script : scripts)
    {
        if(script->IsActive())
            script->Execute();
    }
}
