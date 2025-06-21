#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 u_MVP;

out vec4 world_pos;
void main()
{
    gl_Position = u_MVP * vec4(pos.x, pos.y, pos.z, 1.0);
    world_pos = gl_Position;
}
