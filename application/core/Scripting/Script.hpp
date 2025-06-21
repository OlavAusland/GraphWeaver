#pragma once
#include <string>
#include <sys/stat.h>
#include <vector>
#include <string>

class Script
{
protected:
    std::string filename;
    std::string file;
    struct stat info;
    FILE* file_ptr;

    bool is_active;

    std::vector<std::string> info_messages;
public:
    Script(std::string file);

    void SetExecutingScript(Script* script) const;
    virtual void Execute() = 0;
    
    bool HasChanged();
    const std::string& GetName();
    bool* GetIsEnableRef();
    const bool& IsActive() const;
};

Script* GetExecutingScript();
