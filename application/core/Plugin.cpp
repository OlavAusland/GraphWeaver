#include "EventManager.hpp"
#include "Plugin.hpp"
#include <dlfcn.h>
#include <string>
#include <stdio.h>
#include <regex>
#include <unistd.h>
Plugin::Plugin(std::string filename)
    : filename(filename), plugin_name(filename), need_reload(false), enabled(false), address(nullptr)
{
    if(stat(filename.c_str(), &info) != 0)
    {
        printf("[INFO] Failed To Read File\r\n");
        return;
    }
    /*
    address = dlopen(filename.c_str(), RTLD_NOW);

    if(address == NULL)
    {
        printf("[ INFO ] Failed to load shared library\n");
        return;
    }
    */
    std::cmatch matches;
    std::regex plugin_name_pattern(".*\\/(.*)\\.so");

    if(std::regex_search(filename.c_str(), matches, plugin_name_pattern))
    {
        plugin_name = matches[1].str();
    }
}

int Plugin::Load()
{
    if(stat(filename.c_str(), &info) != 0)
    {
        printf(" [ INFO ] Failed to read file!\n");
        return -1;
    }

    if(enabled == false) { return 0; }

    if(address != nullptr) 
    {
        dlclose(address); 
    }

    address = dlopen(filename.c_str(), RTLD_NOW | RTLD_DEEPBIND);

    if(address == nullptr)
    {
        //printf("[ INFO ] dlopen() failed!\n");
        return -1;
    }
    
    printf("[ INFO ] Reloaded: %s\n", filename.c_str());
    need_reload = false;
    
    return 0;
}

int Plugin::Unload()
{
    dlclose(address);
    
    address = nullptr;

    return 0;
}

bool Plugin::HasChanged()
{
    struct stat updated_info;
    if(stat(filename.c_str(), &updated_info) == 0)
    {
        if(updated_info.st_mtim.tv_sec != info.st_mtim.tv_sec)
        {
            need_reload = true;
            return true;
        }
    }

    return false;
}
