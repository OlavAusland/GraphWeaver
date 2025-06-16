#pragma once
#include "Plugin.hpp"
#include <vector>


class PluginManager
{
private:
    static std::string plugin_path;
public:
    static std::vector<Plugin> plugins;
public:
    PluginManager() = delete;

    static int AddPlugin(std::string filename);
    static void Update();
    static void LoadPlugins();
    static std::vector<Plugin>& GetPlugins();
};
