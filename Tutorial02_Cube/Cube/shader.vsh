#version 300 es
precision mediump float;
layout(location = 0) in vec3 m_position;
layout(location = 1) in vec4 m_color;
uniform mat4 m_mvp;
out vec4 m_outColor;

void main()
{
	vec4 pos = vec4(m_position, 1);
	gl_Position = m_mvp * pos;
	m_outColor = m_color;
}
