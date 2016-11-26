#version 300 es
precision mediump float;
in vec4 m_outColor;
out vec4 o_fragColor;

void main()
{
	o_fragColor = m_outColor;
}
