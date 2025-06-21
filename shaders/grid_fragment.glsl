#version 330 core

precision highp float;

uniform vec3 u_scale;
uniform vec4 u_color;
in vec3 frag_pos;

out vec4 FragColor;

void main()
{
    float spacing = 1;
    float thickness = 0.05 * spacing;

    float dist_x = abs(mod(frag_pos.x * spacing, spacing));
    float dist_z = abs(mod(frag_pos.z * spacing, spacing));

    float distance = length(frag_pos.xz);
    float fade = exp(-distance * 0.05);

    if (dist_x > thickness && dist_z > thickness)
        discard;

    FragColor = vec4(u_color.xyz, min(0.025, fade));
}

