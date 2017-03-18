#version 330

layout( location = 0 ) in vec4 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec4 color;


uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix = ma4(1.0);


out DATA
{

	vec4 position;
	vec4 color;
	vec3 normals;
	vec3 fragmentPosition;

} vs_out;


void main()
{

	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position.x, position.y, position.z, 1.0f);
	vs_out.position =  projection_matrix * view_matrix *  model_matrix * position;
	vs_out.color = color;
	vs_out.normals = normal;
	vs_out.fragmentPosition = vec3(vec4(position.x, position.y, position.z, 1.0f));

}