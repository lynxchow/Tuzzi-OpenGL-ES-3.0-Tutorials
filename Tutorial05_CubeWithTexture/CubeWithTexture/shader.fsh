#version 300 es
precision mediump float;
layout(location = 0) out vec4 outColor;
in vec2 v_texCoord;
uniform sampler2D s_texture;

void main()
{
	outColor = texture(s_texture, v_texCoord);
}
