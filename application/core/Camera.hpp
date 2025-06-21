#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

enum class ProjectionType
{
    Orthogonal,
    Perspective
};

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
public:
    glm::mat4 view;

    glm::mat4 orthogonal_matrix;
    glm::mat4 perspective_matrix;
public:
    ProjectionType active_projection;
private:
public:
    Camera();

    void Update();

    glm::mat4& operator()()
    {
        if(active_projection == ProjectionType::Orthogonal)
        {
            return orthogonal_matrix;
        }
        
        return perspective_matrix;
    }

    const ProjectionType& GetPerspectiveType() const;
    void SetPerspectiveType(ProjectionType type);
    glm::mat4& GetCameraMatrix();

    void SetPosition(glm::vec3 position);
    void Move(glm::vec3 vector);
};


void SetActiveCamera(Camera& camera);
Camera& GetActiveCamera();
