#include "DrawManager.hpp"
#include <string>
#include <unordered_map>
#include <memory>

std::unordered_map<std::string, std::unique_ptr<DrawObject>> DrawManager::objects;
GraphWeaver::Color DrawManager::color = {1.0f, 0.5f, 0.2f, 1.0f};

/*
 * Add sone logic to chance the draw order
 */
void DrawManager::Draw()
{
    for(auto const& object : objects)
    {
        object.second->Draw();
        //printf("[ INFO ] Drawing %s\n", object.first.c_str());
    }
}

void DrawManager::SetColor(float r, float g, float b, float a)
{
    color = {r, g, b, a};
}

const GraphWeaver::Color& DrawManager::GetActiveColor()
{
    return color;
}

void DrawManager::AddObject(std::string id, std::unique_ptr<DrawObject> obj)
{
    objects[id] = std::move(obj);
}

std::unique_ptr<DrawObject>* DrawManager::GetObject(char* id)
{
    if(objects.find(id) == objects.end())
        return nullptr;

    return &objects[id];
}
