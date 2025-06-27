#define PYTHON_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <vector>
#include "Graphics.hpp"
#include "Canvas.hpp"
#include "SDL3/SDL.h"

#include "Shader.hpp"
#include "DrawManager.hpp"
#include "PointObject.hpp"
#include "Script.hpp"

using namespace GraphWeaver;


static PyObject* set_color(PyObject* self, PyObject* args)
{
    char* id;
    float r, g, b, a;

    if(!PyArg_ParseTuple(args, "sffff", &id, &r, &g, &b, &a))
    {
        Py_RETURN_NONE;
    }
    
    std::unique_ptr<DrawObject>* obj = DrawManager::GetObject(id);
   
    if(obj == nullptr || obj->get() == nullptr){ Py_RETURN_NONE; }
    
    (*obj)->SetColor(r, g, b, a);

    Py_RETURN_NONE;
}

static PyObject* draw_line(PyObject* self, PyObject* args)
{
    DrawObject* obj;

    char* id;
    PyObject* input_obj_x = nullptr;
    PyObject* input_obj_y = nullptr;
    if(!PyArg_ParseTuple(args, "sOO", &id, &input_obj_x, &input_obj_y))
    {
        Py_RETURN_NONE;
    }

    if(DrawManager::GetObject(id) == nullptr)
    {
        printf("[ INFO ] Created a new DrawObject (LineObject)\n");
        DrawManager::AddObject(id, std::make_unique<LineObject>(GL_LINE_STRIP));
        DrawManager::GetObject(id)->get()->SetScriptOwner(GetExecutingScript());
            
    }
    obj = DrawManager::GetObject(id)->get();
    obj->Clear();

    if(Py_TYPE(input_obj_x) != &PyList_Type)
    {
        Py_RETURN_NONE;
    }

    Py_ssize_t size_x = PyList_GET_SIZE(input_obj_x);
    Py_ssize_t size_y = PyList_GET_SIZE(input_obj_y);
    
    const Vec3& origo = Canvas::GetOrigo();
    const Vec3& scale = Canvas::GetScale();
    const Vec2& bounds = Canvas::GetBounds();
    
    PyObject* x;
    PyObject* y;
    float value_x = 0;
    float value_y = 0;
    for(int i = 0; i < size_x; i++)
    {
        y = PyList_GetItem(input_obj_y, i);
        x = PyList_GetItem(input_obj_x, i);
        
        value_x = PyFloat_AsDouble(x);
        value_y = PyFloat_AsDouble(y);
        obj->AddPoint({value_x, value_y, 0});
    }

    Py_RETURN_NONE;
}
static PyObject* draw_points(PyObject* self, PyObject* args)
{
    //static const GraphWeaver::Color& color = DrawManager::GetActiveColor();
    std::unique_ptr<DrawObject>* point_object;

    char* id;
    PyObject* input_obj_x = nullptr;
    PyObject* input_obj_y = nullptr;

    if(!PyArg_ParseTuple(args, "sOO", &id, &input_obj_x, &input_obj_y))
    {
        Py_RETURN_NONE;
    }

    if(Py_TYPE(input_obj_x) != &PyList_Type)
    {
        Py_RETURN_NONE;
    }

    if(DrawManager::GetObject(id) == nullptr)
    {
        printf("[ INFO ] Created a new DrawObject (PointObject)\n");
        DrawManager::AddObject(id, std::make_unique<PointObject>());
        DrawManager::GetObject(id)->get()->SetScriptOwner(GetExecutingScript());
    }
    point_object = DrawManager::GetObject(id);
    point_object->get()->Clear();

    Py_ssize_t size_x = PyList_GET_SIZE(input_obj_x);
    Py_ssize_t size_y = PyList_GET_SIZE(input_obj_y);
    
    const Vec3& origo = Canvas::GetOrigo();
    const Vec3& scale = Canvas::GetScale();
    const Vec2& bounds = Canvas::GetBounds();
    
    PyObject* x;
    PyObject* y;
    float value_x = 0;
    float value_y = 0;
    for(int i = 0; i < size_x; i++)
    {
        y = PyList_GetItem(input_obj_y, i);
        x = PyList_GetItem(input_obj_x, i);
        
        value_x = PyFloat_AsDouble(x);
        value_y = PyFloat_AsDouble(y);
        
        point_object->get()->AddPoint({value_x, value_y, 0});
    }

    Py_RETURN_NONE;
}


static PyMethodDef AvailableMethods[] = {
    {"draw_points", draw_points,METH_VARARGS, "Test1"},
    {"draw_line",   draw_line,  METH_VARARGS, "Test2"},
    {"set_color",   set_color,  METH_VARARGS, "Test3"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "graph_weaver",
    NULL,
    -1,
    AvailableMethods
};

PyMODINIT_FUNC PyInit_graph_weaver(void)
{
    printf("[ INFO ] Initialized Graph Weaver\n");
    return PyModule_Create(&module);
}
