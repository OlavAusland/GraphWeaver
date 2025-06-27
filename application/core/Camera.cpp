#include "Camera.hpp"
#include "Canvas.hpp"

static Camera* active_camera = nullptr;

void SetActiveCamera(Camera& camera)
{
    active_camera = &camera;
}

Camera& GetActiveCamera()
{
    return *active_camera;
}

Camera::Camera()
:   
    position(0.0f, 0.0f, 10.0f),
    forward(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    view(glm::lookAt(position, forward, up)),
    active_projection(ProjectionType::Orthogonal),
    orthogonal_matrix(1.0f),
    perspective_matrix(1.0f)
{
}

void Camera::Update()
{
    const float& aspect = Canvas::GetAspect();
    Vec3& scale         = Canvas::GetScale();
    Vec2& bounds        = Canvas::GetBounds();


    view = glm::lookAt(position, forward, up);
    
    if(active_projection == ProjectionType::Orthogonal)
    {
        orthogonal_matrix = glm::ortho(
                -(scale.x / 2.0f) * Canvas::GetAspect(),
                (scale.x / 2.0f) * Canvas::GetAspect(), 
                -(scale.y / 2.0f),
                (scale.y / 2.0f), 
                0.0f, 100.0f);
    }
    else
    {
        perspective_matrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
    }

    glm::vec3 position = glm::vec3(0.0, 0.0, 10.0f);
}

const ProjectionType& Camera::GetPerspectiveType() const
{
    return active_projection;
}

void Camera::SetPerspectiveType(ProjectionType type)
{
    active_projection = type;
}
glm::mat4& Camera::GetCameraMatrix()
{
    return orthogonal_matrix;
}

void Camera::SetPosition(glm::vec3 position)
{
    this->position = position;
}

void Camera::Move(glm::vec3 vec)
{
    position = {position.x + vec.x, position.y + vec.y, position.z + vec.z};
}
