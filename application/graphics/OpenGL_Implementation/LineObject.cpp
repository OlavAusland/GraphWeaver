#include "LineObject.hpp"
#include "ShaderManager.hpp"
#include "Canvas.hpp"
#include "Camera.hpp"
#include "Utils.hpp"
#include <glad/glad.h>
#include "Shader.hpp"
#include <stdio.h>

LineObject::LineObject(int draw_mode)
    : DrawObject(), draw_mode(draw_mode)
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
    if(master != nullptr && !master->IsActive()){ return; }
    static Camera& camera = GetActiveCamera();
    Vec3& origo = Canvas::GetOrigo();

    glm::mat4 model(1.0f);
    model = glm::translate(model, {origo.x, origo.y, origo.z});

    shader.SetActive();
    shader.SetUniformMatrix4fv("u_MVP", camera() * camera.view * model);
    shader.SetUniform4f("u_color", {color.r, color.g, color.b, 1.0});

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GraphWeaver::Vec3) * points.size(), points.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(VAO);
    glDrawArrays(draw_mode, 0, points.size());
}
