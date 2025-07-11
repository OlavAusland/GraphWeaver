#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(pos.x, pos.y, pos.z, 1.0);
    //gl_Position = pos;
    gl_PointSize = 14;
}

