#include "PointObject.hpp"
#include <glad/glad.h>

PointObject::PointObject()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void PointObject::Draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GraphWeaver::Vec3) * points.size(), points.data(), GL_DYNAMIC_DRAW);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, points.size());
}

void PointObject::Clear()
{
    points.clear();
}

void PointObject::AddPoint(GraphWeaver::Vec3 point)
{
    points.push_back(point);
}
