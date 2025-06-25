#pragma once
#include "Scripting/Script.hpp"
#include <vector>
#include <stdint.h>
#include <string>
#include <memory>

class Entity
{
private:
    std::string name;
private:
    void* data;
    uint64_t data_size;

    bool m_is_active;
    
public:
    Entity(std::string name);
    std::vector<std::unique_ptr<Script>> scripts;

    void SetName(char* new_name);
    const std::string& GetName() const;

    void AddScript(std::string file);
    const bool IsActive() const;
    bool* IsActivePtr();

    void ExecuteAll();
};
