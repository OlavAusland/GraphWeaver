#include "PyScript.hpp"
#include "Python.h"
#include "object.h"
#include "pyerrors.h"
#include <fstream>
#include <iterator>
#include <regex>


static std::regex filename_regex(R"([^/]+.py)");

PyScript::PyScript(std::string file)
    : Script(file), locals(PyDict_New()), globals(PyDict_New()), compiled_code(nullptr)
{
    std::smatch regex_match;

    if(std::regex_search(file, regex_match, filename_regex))
    {
        printf("[ REGEX ] Matched %s\n", regex_match.str().c_str());
        filename = regex_match.str();
    }
}

void PyScript::GetErrorMessage()
{
    PyObject *type, *value, *traceback;

    PyErr_Fetch(&type, &value, &traceback);
    PyErr_NormalizeException(&type, &value, &traceback);

    PyObject* str_exec_value = PyObject_Str(value);

    info_messages.push_back(PyUnicode_AsUTF8(str_exec_value));
}

void PyScript::Compile()
{
    std::ifstream filestream(file); 
    std::string buffer{std::istreambuf_iterator<char>(filestream), std::istreambuf_iterator<char>()};
    
    compiled_code = Py_CompileString(buffer.c_str(), "test", Py_file_input);

    if(compiled_code == nullptr)
    {
        printf("[ ERROR ] Failed to compile: %s\n", file.c_str());
        PyErr_Print();
        return;
    }
    
    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
    PyEval_EvalCode(compiled_code, globals, globals);

    PyObject* function = PyDict_GetItemString(globals, "graph_weaver_init");
    
    if(function)
    {
        function_map["graph_weaver_init"] = function;
        PyObject_CallObject(function, nullptr);

        PyErr_Print();
    }


    function = PyDict_GetItemString(globals, "graph_weaver_update");


    if(function)
    {
        function_map["graph_weaver_update"] = function;

    }
}

void PyScript::Execute()
{
    if(!IsActive()){ printf("NOT ACTIVE\n");return; }
    
    SetExecutingScript(this);

    if(HasChanged() || compiled_code == nullptr)
    {
        Compile();
    }

    if(function_map["graph_weaver_update"])
    {
        PyObject_CallObject(function_map["graph_weaver_update"], nullptr);
    }
}
