#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 outColor;
out vec3 Normal;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec3 FragPos;


void main()
{
    gl_Position = proj * view * model * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	outColor = vec3(1.0f, 1.0f, 0.0f);

	Normal = aNormal;
}