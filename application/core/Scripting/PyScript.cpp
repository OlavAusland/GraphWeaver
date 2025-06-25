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

    Compile();
}

void PyScript::GetErrorMessage()
{
    PyObject *type, *value, *traceback;

    PyErr_Fetch(&type, &value, &traceback);

    if(type == nullptr || value == nullptr)
        return;

    PyErr_NormalizeException(&type, &value, &traceback);

    PyObject* string = PyObject_Str(value);
    
    PyObject* error_type_obj = PyObject_GetAttrString(type, "__name__");
    const char* error_type = PyBytes_AsString(PyUnicode_AsUTF8String(PyObject_Str(error_type_obj)));

    const char* error = PyBytes_AsString(PyUnicode_AsUTF8String(string));

    Console::AddMessage({Console::MessageType::Error,
            filename, std::string(error_type) + std::string("\n") + std::string(error)});

    Py_XDECREF(type);
    Py_XDECREF(value);
    Py_XDECREF(traceback);
    Py_XDECREF(string);
}

CompileResult PyScript::Compile()
{
    std::ifstream filestream(file); 
    std::string buffer{std::istreambuf_iterator<char>(filestream), std::istreambuf_iterator<char>()};
    
    if(compiled_code != nullptr)
    {
        Py_XDECREF(compiled_code);
        Py_XDECREF(globals);
        globals = PyDict_New();
        function_map.clear();
    }

    compiled_code = Py_CompileString(buffer.c_str(), filename.c_str(), Py_file_input);

    if(compiled_code == nullptr)
    {
        printf("[ ERROR @ %d ] Failed to compile: %s\n", __LINE__, file.c_str());
        GetErrorMessage();

        return CompileResult::Failed;
    }

    printf("Compile successfully\n");

    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
    PyEval_EvalCode(compiled_code, globals, globals);

    PyObject* function = PyDict_GetItemString(globals, "graph_weaver_init");
    
    if(function)
    {
        function_map["graph_weaver_init"] = function;
        PyObject_CallObject(function, nullptr);
    }


    function = PyDict_GetItemString(globals, "graph_weaver_update");


    if(function)
    {
        function_map["graph_weaver_update"] = function;
    }

    return CompileResult::Successful;
}

void PyScript::Execute()
{
    if(!IsActive()){ printf("NOT ACTIVE\n");return; }
    
    SetExecutingScript(this);

    if(HasChanged())
    {
        Compile();
    }

    if(function_map["graph_weaver_update"])
    {
        PyObject_CallObject(function_map["graph_weaver_update"], nullptr);
        GetErrorMessage();
    }
}
