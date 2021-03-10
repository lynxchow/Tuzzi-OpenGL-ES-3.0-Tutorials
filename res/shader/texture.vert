layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 u_MVP;

out vec2 TexCoord;

void main()
{
	gl_Position = u_MVP * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}
