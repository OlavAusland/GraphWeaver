#version 330 core
out vec4 FragColor;

uniform vec3 u_scale;
uniform vec4 u_color;
uniform vec2 u_resolution;

in vec3 frag_pos;

void main()
{
    if(u_scale.x < 0 || u_scale.y < 0)
        discard;
    // Get pixel width in world space (not screen space)
    float thickness_x = fwidth(frag_pos.x);
    float thickness_y = fwidth(frag_pos.y);

    // Repeat every u_scale.x / 10 units
    float spacing_x = u_scale.x / 10.0;
    float spacing_y = u_scale.y / 10.0;

    float draw_x = mod(frag_pos.x, spacing_x);
    float draw_y = mod(frag_pos.y, spacing_y);

    // Draw lines of 1-pixel thickness in world space
    if(draw_x > thickness_x && draw_y > thickness_y)
        discard;

    FragColor = vec4(u_color.xyz, 0.2);
}

