precision mediump float;
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D faceTexture;
uniform sampler2D backTexture;

void main()
{
    if (gl_FrontFacing)
    {
        FragColor = texture(faceTexture, TexCoord);
    }
    else
    {
        FragColor = texture(backTexture, TexCoord);
    }
	
}
