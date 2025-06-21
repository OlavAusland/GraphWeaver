#include "PlaneObject.hpp"
#include <glad/glad.h>
#include "Camera.hpp"
#include "Canvas.hpp"

PlaneObject::PlaneObject()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
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
    static Camera& camera   = GetActiveCamera();
    static Vec3& origo      = Canvas::GetOrigo();
    static Vec3& scale      = Canvas::GetScale();
    static Vec3& bounds     = Canvas::GetBounds();

    glm::mat4 model(1.0f);
    model = glm::translate(model, {origo.x, origo.y, origo.z});

    shader.Reload();
    shader.SetActive();
    shader.SetUniformMatrix4fv("u_MVP", camera() * camera.view * model);
    shader.SetUniform4f("u_color", {color.r, color.g, color.b, color.a});
    shader.SetUniform3f("u_scale", scale);
    shader.SetUniform2f("u_resolution", {bounds.x, bounds.y});

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GraphWeaver::Vec3) * points.size(), points.data(), GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, points.size());
}
