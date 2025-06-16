#version 330 core
out vec4 FragColor;

uniform vec3 u_color;

void main()
{
    float dist = length(gl_PointCoord - vec2(0.5));
    
    if(dist > 0.5)
        discard;

    vec3 color = mix(u_color, vec3(0.1f, 0.1f, 0.1f), dist);
    float alpha = smoothstep(0.5, 0.3, dist);

    FragColor = vec4(color, alpha);
}

