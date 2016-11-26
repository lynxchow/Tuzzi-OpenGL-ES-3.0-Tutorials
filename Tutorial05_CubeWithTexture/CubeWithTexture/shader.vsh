#version 300 es
precision mediump float;
layout(location = 0) in vec3 m_position;
layout(location = 1) in vec2 a_texCoord;
uniform mat4 m_mvp;
out vec2 v_texCoord;

void main()
{
	vec4 pos = vec4(m_position, 1);
	gl_Position = m_mvp * pos;
	v_texCoord = a_texCoord;
}
