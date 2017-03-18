#version 330

layout ( location = 0 ) out vec4 color;

uniform vec4 col;
uniform vec3 light_pos;
vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

in DATA
{
	vec4 position;
	vec4 color;
	vec3 normals;
	vec3 fragmentPosition;

} fs_in;


void main()
{

	// Ambient Lightning
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse Lightning
	vec3 norm = normalize(fs_in.normals);
	vec3 lightDir = normalize(light_pos - fs_in.fragmentPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * vec3(fs_in.color.xyz);
	color = vec4(result, 1.0f);

	//vec4 intensity = 150.0 / length(fs_in.position.xyz - light_pos) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
	



}
