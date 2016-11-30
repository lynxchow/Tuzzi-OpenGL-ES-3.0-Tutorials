#version 300 es
precision mediump float;
layout(location = 0) out vec4 outColor;
in vec2 v_texCoord;
uniform sampler2D s_texture;
uniform float m_ambient_strength;

void main()
{
    vec3 ambient_color = vec3(1.0, 1.0, 1.0);
    vec3 ambient = m_ambient_strength * ambient_color;
    
	outColor = vec4(ambient, 1.0) * texture(s_texture, v_texCoord);
}
