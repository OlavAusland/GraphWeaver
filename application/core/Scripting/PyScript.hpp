#pragma once
#define PY_SSIZE_T_CLEAN
#include "Script.hpp"
#include "Python.h"
#include <unordered_map>

class PyScript : public Script 
{
private:
    std::unordered_map<std::string, PyObject*> function_map;
private:
    PyObject* locals;
    PyObject* globals;

    PyObject* compiled_code;
private:
    void Compile();

    void GetErrorMessage();
public:
    PyScript(std::string file);
    void Execute() override;
};
