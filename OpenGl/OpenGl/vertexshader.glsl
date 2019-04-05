#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texture;

out vec3 outColor;
out vec2 TexCoord;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	outColor = vec3(1.0f, 1.0f, 0.0f);
	TexCoord = vec2(texture.x, texture.y);
}