#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 u_MVP;

out vec4 shadow_pos;
void main()

{
    gl_Position = u_MVP * vec4(pos.x, pos.y, pos.z, 1.0);
    //gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    shadow_pos = gl_Position;
}
