#version 330

in vec2 texCoords;
out vec4 color;

uniform sampler2D tex;
uniform vec3 spriteColor;

void main()
{

	vec4 texColor = texture(tex,texCoords);

	if(texColor.a == 0)
	{
	  discard;
	}

	color = vec4(spriteColor,1.0) * texColor;
}