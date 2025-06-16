#include "LineObject.hpp"
#include "Canvas.hpp"
#include <glad/glad.h>
#include <stdio.h>

LineObject::LineObject(int draw_mode)
    : draw_mode(draw_mode)
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void LineObject::AddPoint(GraphWeaver::Vec3 point)
{
    points.push_back(point);
}

void LineObject::Clear()
{
    points.clear();
}

void LineObject::Draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GraphWeaver::Vec3) * points.size(), points.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(VAO);
    glDrawArrays(draw_mode, 0, points.size());
}
