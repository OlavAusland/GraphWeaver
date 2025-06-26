#include "PlaneObject.hpp"
#include <glad/glad.h>
#include "Camera.hpp"
#include "Canvas.hpp"

PlaneObject::PlaneObject()
{

    shader = Shader("/home/olav/Documents/C++/GraphWeaver/shaders/grid_vertex.glsl",
                           "/home/olav/Documents/C++/GraphWeaver/shaders/grid_fragment.glsl");
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

PlaneObject::PlaneObject(Shader shader)
:   PlaneObject()
{
    this->shader = shader;
}

void PlaneObject::AddPoint(GraphWeaver::Vec3 point)
{
    points.push_back(point);
}

void PlaneObject::Clear()
{
    points.clear();
}

void PlaneObject::Draw()
{
    shader.Reload();
    shader.SetActive();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GraphWeaver::Vec3) * points.size(), points.data(), GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, points.size());
}
