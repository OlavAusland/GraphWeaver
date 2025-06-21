#version 330 core
out vec4 FragColor;

uniform vec4 u_color;

void main()
{
    FragColor = u_color;
    //Fragcolor = vec4(1.0, 0.5, 0.2, 1.0);
}
