#version 300 es
precision mediump float;
layout(location = 0) out vec4 outColor;
in vec2 v_texCoord;
in vec3 m_outNormal;
in vec3 m_outFragPos;
uniform sampler2D s_texture;

void main()
{
    vec3 light = vec3(1.0, 1.0, 1.0);
    
    vec3 light_direct = normalize(vec3(0.0, 3.0, 2.0) - m_outFragPos);
    
    vec3 normal = normalize(m_outNormal);
    
    vec3 df = max(0.0, dot(normal, light_direct)) * light;
    
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * light;
    vec3 result = (ambient + df) * vec3(texture(s_texture, v_texCoord));
    outColor = vec4(result, 1.0);
}
