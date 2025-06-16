#pragma once
#include <vector> // might want to change to a faster data structure
#include <memory>
#include "DrawObject.hpp"
#include <unordered_map>

class DrawManager
{
private:
    static std::unordered_map<std::string, std::unique_ptr<DrawObject>> objects;
    static GraphWeaver::Color color;
public:
    DrawManager() = delete;
    
    static void SetColor(float r, float g, float b, float a = 1);
    static const GraphWeaver::Color& GetActiveColor();

    static void Draw();
    static std::unique_ptr<DrawObject>* GetObject(char* id);
    static void AddObject(std::string id, std::unique_ptr<DrawObject> object);
};
