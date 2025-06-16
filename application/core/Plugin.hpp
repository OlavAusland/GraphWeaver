#pragma once
#include <sys/types.h>
#include <sys/stat.h>

#include <string>

class Plugin
{
public:
    bool enabled;
    bool need_reload;
    struct stat info;
    std::string plugin_name;
private:
    void* address;
    std::string filename;

public:
    Plugin(std::string filename);
    
    bool HasChanged();
    int Unload();
    int Load();
};
