#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texture;

out vec3 outColor;
out vec2 TexCoord;
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	outColor = aColor;
	TexCoord = vec2(texture.x, texture.y);
}