#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <regex>
#include "Script.hpp"

static Script* active_script;


Script* GetExecutingScript()
{
    return active_script;
}

void Script::SetExecutingScript(Script* script) const
{
    active_script = script;
}

Script::Script(std::string file)
    : file(file), is_active(true)
{
    file_ptr = fopen(file.c_str(), "r");

    if(file_ptr == nullptr)
    {
        printf("[ INFO ] Failed to open file!\n");
        return;
    }

    printf("[ INFO ] Loaded: %s\n", file.c_str());

    stat(file.c_str(), &info);
}

bool Script::HasChanged()
{
    struct stat current_info;
    if(stat(file.c_str(), &current_info) == 0)
    {
        if(current_info.st_mtim.tv_sec != info.st_mtim.tv_sec)
        {
            info = current_info;
            return true;
        }
    }


    return false;
}

const std::string& Script::GetName()
{
    return filename;
}

const bool& Script::IsActive() const
{
    return is_active;
}

bool* Script::GetIsEnableRef()
{
    return &is_active;
}
