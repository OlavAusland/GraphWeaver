#include "PluginManager.hpp"
#include "Plugin.hpp"
#include <string>
#include <fstream>
#include <unistd.h>
#include <limits.h>
#include <filesystem>
#include <regex>

std::string PluginManager::plugin_path;
std::vector<Plugin> PluginManager::plugins;

std::vector<Plugin>& PluginManager::GetPlugins()
{
    return plugins;
}


int PluginManager::AddPlugin(std::string filename)
{
    if(!std::ifstream(filename))
    {
        printf("Invalid File!\r\n");
        return -1;
    }

    Plugin plugin(filename);
    plugins.push_back(plugin);
    
    return 0;
}

void PluginManager::Update()
{
    for(Plugin& plugin : plugins)
    {
        if(plugin.HasChanged() || plugin.need_reload)
        {
            //plugin.Unload();
            plugin.Load();
        }
    }
}

void PluginManager::LoadPlugins()
{
    namespace fs = std::filesystem;
    
    plugins.clear();

    char path[PATH_MAX];
    size_t count = readlink("/proc/self/exe", path, PATH_MAX);
    
    fs::path plugins_dir(path);
    plugins_dir = plugins_dir.parent_path().parent_path();
    plugins_dir.append("plugins");

    std::smatch matches;
    std::regex plugin_pattern("(\\/[^\\/]+)+\\/([^\\/]+)(\\/build)?\\/(lib)?\\2.so");
    
    std::string test;
    for(auto const& entry : fs::recursive_directory_iterator(plugins_dir))
    {
        std::string entry_str(entry.path().u8string());

        if(!std::regex_match(entry.path().c_str(), plugin_pattern)){ continue; }
        printf("[ INFO ] Added Plugin: %s\n", entry.path().c_str());
        AddPlugin(entry.path());
    }
}


