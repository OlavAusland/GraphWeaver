#pragma once
#include <string>
#include <sys/stat.h>
#include <string>

class Script
{
protected:
    std::string filename;
    std::string file;
    struct stat info;
    FILE* file_ptr;

    bool is_active;
public:
    Script(std::string file);

    void SetExecutingScript(Script* script) const;
    virtual void Execute() = 0;
    
    bool HasChanged();
    const std::string& GetName() const;
    bool* GetIsEnableRef();
    const bool& IsActive() const;
};

Script* GetExecutingScript();
