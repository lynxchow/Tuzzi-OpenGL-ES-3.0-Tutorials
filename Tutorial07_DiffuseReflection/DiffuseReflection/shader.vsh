#version 300 es
precision mediump float;
layout(location = 0) in vec3 m_position;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec3 m_normal;
uniform mat4 m_mvp;
uniform mat4 m_model;
uniform mat4 m_modelNormal;
out vec2 v_texCoord;
out vec3 m_outNormal;
out mat4 m_outModelNormal;
out vec3 m_outFragPos;

void main()
{
	vec4 pos = vec4(m_position, 1);
	gl_Position = m_mvp * pos;
	v_texCoord = a_texCoord;
    m_outNormal = mat3(m_modelNormal) * m_normal;
    m_outFragPos = vec3(m_model * vec4(m_position, 1));
}
