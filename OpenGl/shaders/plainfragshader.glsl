#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	//vec3 lightColor = vec3(1.0f, 0.5f, 0.31f);
	//vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * objectColor;
	
	FragColor = vec4(result, 1.0);
}