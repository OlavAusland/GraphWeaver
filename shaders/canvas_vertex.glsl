#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 u_MVP;

out vec3 frag_pos;
void main()
{
    frag_pos = pos;
    gl_Position = u_MVP * vec4(pos.x, pos.y, pos.z, 1.0);
}

