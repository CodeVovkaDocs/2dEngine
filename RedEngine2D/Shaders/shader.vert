#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 mvp;
uniform vec4 texShift;


out vec2 texCoords;

void main()
{	
	gl_Position = mvp * vec4(pos, 1.0);
	texCoords = vec2(tex.x / texShift.w + texShift.x , tex.y / texShift.z + texShift.y );
}