#include "PointObject.hpp"
#include <glad/glad.h>
#include "Camera.hpp"
#include "Utils.hpp"
#include "Canvas.hpp"
#include "ShaderManager.hpp"

PointObject::PointObject()
    : DrawObject()
{
    shader = Shader("/home/olav/Documents/C++/GraphWeaver/shaders/point_vertex.glsl",
                           "/home/olav/Documents/C++/GraphWeaver/shaders/point_fragment.glsl");
    
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void PointObject::Draw()
{
    if(master != nullptr)
    {
        if(!master->IsActive()){ return; }
    }
    static Camera& camera = GetActiveCamera();
    Vec3& origo = Canvas::GetOrigo();

    glm::mat4 model(1.0f);
    model = glm::translate(model, {origo.x, origo.y, origo.z});

    shader.SetActive();
    shader.SetUniformMatrix4fv("u_MVP", camera() * camera.view * model);
    shader.SetUniform3f("u_color", {1.0, 0.5, 0.2});
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
